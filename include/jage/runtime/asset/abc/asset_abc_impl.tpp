template<class T>
void jage::runtime::asset::abc::AssetABC<T>::enqueue() {
    enqueue(JAGE_ASSET_BASE_PRIORITY);
}

template<class T>
void jage::runtime::asset::abc::AssetABC<T>::enqueue(int priority) {
    if (isReady())
        return;
    onQueue(priority);
}

template<class T>
void jage::runtime::asset::abc::AssetABC<T>::prepare() {
    if (isPrepared() or !isProcessed())
        return;
    onPrepare();
    m_prepared = true;
}

template<class T>
bool jage::runtime::asset::abc::AssetABC<T>::isProcessed() const {
    return m_processed;
}

template<class T>
bool jage::runtime::asset::abc::AssetABC<T>::isPrepared() const {
    return m_prepared;
}

template<class T>
bool jage::runtime::asset::abc::AssetABC<T>::isReady() const {
    return m_prepared;
}

template<class T>
jage::runtime::asset::abc::AssetABC<T>& jage::runtime::asset::abc::AssetABC<T>::asAsset() {
    return *this;
}

template<class T>
T& jage::runtime::asset::abc::AssetABC<T>::asObject() {
    return dynamic_cast<T&>(*this);
}

template<class T>
void jage::runtime::asset::abc::AssetABC<T>::markProcessed() {
    m_processed = true;
}
