template<class T>
void jage::runtime::asset::abc::AssetABC<T>::queue() {
    queue(JAGE_ASSET_BASE_PRIORITY);
}

template<class T>
jage::runtime::asset::abc::AssetABC<T>& jage::runtime::asset::abc::AssetABC<T>::asAsset() {
    return *this;
}

template<class T>
T& jage::runtime::asset::abc::AssetABC<T>::asObject() {
    return dynamic_cast<T&>(*this);
}
