template<class T>
std::shared_ptr<T> jage::runtime::asset::AssetManager::load(const std::string &fileName, int priority /* = JAGE_ASSET_BASE_PRIORITY */) {
    auto model = T::create(fileName);
    model->queue(priority);
    return model;
}