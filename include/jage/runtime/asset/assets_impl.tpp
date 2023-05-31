template<class T>
std::shared_ptr<T> jage::runtime::asset::Assets::get(std::string filePath, int priority /* = JAGE_ASSET_BASE_PRIORITY */) {
    return AssetManager::getInstance()->get<T>(std::move(filePath), priority);
}

template<class T>
std::shared_ptr<T> jage::runtime::asset::Assets::get() {
    return AssetManager::getInstance()->getDefault<T>();
}