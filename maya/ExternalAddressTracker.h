//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_EXTERNALADDRESSTRACKER_H
#define MAYA_EXTERNALADDRESSTRACKER_H
#include <map>
#include "Problem.h"
namespace maya {
        /**
         * @brief Track the type code generated from registering a type
         */
        template<typename T>
        class ExternalAddressTracker final {
            public:
            ExternalAddressTracker() = delete;
            ~ExternalAddressTracker() = delete;
            ExternalAddressTracker(ExternalAddressTracker&&) = delete;
            ExternalAddressTracker(const ExternalAddressTracker&) = delete;
            ExternalAddressTracker& operator=(const ExternalAddress&) = delete;
            ExternalAddressTracker& operator=(ExternalAddress&&) = delete;
            static int getExternalAddressId(Environment* env) {
                return getExternalAddressId_Internal(env);
            }
            static void registerExternalAddressId(Environment* env, int result) {
                registerExternalAddressId_Internal(env, result);
            }
            private:
            static int getExternalAddressId_Internal(void* env) {
                if (auto found = _cache.find(env); found != _cache.end()) {
                    return found->second;
                } else {
                    throw Problem("Attempted to get the external address index of something not registered from using an unregistered environment");
                }
            }
            static void registerExternalAddressId_Internal(void* env, int result) {
                _cache.emplace(env, result);
            }
            static std::map<void*, int> _cache;
        };
        template<typename T>
        std::map<void*, int> ExternalAddressTracker<T>::_cache;

}
#endif //MAYA_EXTERNALADDRESSTRACKER_H
