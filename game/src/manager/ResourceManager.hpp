#ifndef ZENIT_RESOURCEMANAGER_HPP
#define ZENIT_RESOURCEMANAGER_HPP

#include <thread>
#include <any>
#include <queue>
#include <map>
#include <string>
#include <typeindex>
#include <memory>
#include <functional>
#include "TK/engine/utils/Log.hpp"

/**
 * A simple ResourceManager that contains all the live resources in the game as a shared pointer.
 * @author
 */
class ResourceManager {
public:
    static ResourceManager &get() {
        static ResourceManager instance;
        return instance;
    }

    template<typename T>
    void addResourceLoader(std::function<std::shared_ptr<T>(const std::string &)> loaderFunc) {
        m_resourceLoaders[typeid(T)] = loaderFunc;
    }

    template<typename T>
    void loadResourceDirectly(const std::string &relativePath) {
        if (m_resources.count(relativePath)) {
            TK_LOG("ResourceManager") << "Resource already loaded: " << relativePath;
            return;
        }
        auto it = m_resourceLoaders.find(typeid(T));
        if (it != m_resourceLoaders.end()) {
            auto loaderFunc = it->second;
            std::shared_ptr<void> resource = loaderFunc(relativePath);
            m_resources[relativePath] = resource;
        } else {
            TK_LOG_F("ResourceManager") << "Resource loader not registered for the specified type.";
        }
    }

    template<typename T>
    void addResource(const std::string &relativePath, std::shared_ptr<T> resource) {
        if (m_resources.count(relativePath)) {
            TK_LOG("ResourceManager") << "Resource already loaded: " << relativePath;
            return;
        }
        m_resources[relativePath] = resource;
    }


    template<typename T>
    void enqueueResource(const std::string &relativePath) {
        if (m_resources.count(relativePath)) {
            TK_LOG("ResourceManager") << "Resource already loaded: " << relativePath;
            return;
        }
        auto it = m_resourceLoaders.find(typeid(T));
        if (it != m_resourceLoaders.end()) {
            QueueItem queueItem = QueueItem{relativePath, typeid(T)};
            m_queue.push(queueItem);
        } else {
            TK_LOG_F("ResourceManager") << "Resource loader not registered for the specified type.";
        }
    }

    void startLoading() {
        m_finishedQueuedItems = 0;
        m_queueStartSize = m_queue.size();
        while (!m_queue.empty()) {
            const QueueItem &queueItem = m_queue.front();
            auto it = m_resourceLoaders.find(queueItem.type);
            if (it != m_resourceLoaders.end()) {
                auto loaderFunc = it->second;
                std::shared_ptr<void> resource = loaderFunc(queueItem.relativePath);
                m_resources[queueItem.relativePath] = resource;
                m_queue.pop();
                m_finishedQueuedItems++;
            } else {
                TK_LOG_F("ResourceManager") << "Resource loader not registered for the specified type.";
            }
        }
    }

    void startLoadingAsync() {
        m_queueStartSize = m_queue.size();
        std::thread loadingThread([this]() {
            startLoading();
        });
        loadingThread.detach();
    }

    [[nodiscard]] float getProgress() const {
        if (m_queueStartSize == 0) return 1;
        return float(m_finishedQueuedItems) / float(m_queueStartSize);
    }

    template<typename T>
    std::shared_ptr<T> getResource(const std::string &relativePath) {
        auto it = m_resources.find(relativePath);
        if (it != m_resources.end()) {
            auto resource = std::static_pointer_cast<T>(it->second);
            if (resource) {
                return resource;
            }
        }
        TK_LOG_F("ResourceManager") << "Resource not found or type mismatch.";
    }


private:
    struct QueueItem {
        std::string relativePath;
        std::type_index type;
    };
    std::map<std::string, std::shared_ptr<void>> m_resources;
    std::map<std::type_index, std::function<std::shared_ptr<void>(const std::string &)>> m_resourceLoaders;
    std::queue<QueueItem> m_queue;
    u_long m_finishedQueuedItems = 0;
    u_long m_queueStartSize = 0;

    ResourceManager() {};
    ~ResourceManager() = default;
};

#endif
