template<class T>
std::shared_ptr<T> jage::runtime::asset::AssetManager::get(std::mutex& mutex, AssetMap<T>& map, const std::string& fileName, int priority /* = JAGE_ASSET_BASE_PRIORITY */) {
    std::lock_guard<std::mutex> lock(mutex);
    if (map.find(fileName) == map.end()) {
        auto result = load<T>(fileName, priority);
        map[fileName] = result;
    }
    return std::static_pointer_cast<T>(map.at(fileName));
}

template<class T>
std::shared_ptr<T> jage::runtime::asset::AssetManager::load(const std::string &fileName, int priority /* = JAGE_ASSET_BASE_PRIORITY */) {
    std::shared_ptr<T> model = T::create(fileName);
    model->enqueue(priority);
    return model;
}