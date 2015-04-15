#include "imagecache.h"

ImageCache::ImageCache() {
    cachedImages = new QList<CacheObject*>();
    applySettings();
    connect(globalSettings, SIGNAL(settingsChanged()),
            this, SLOT(applySettings()));
}

// call when changing directory
void ImageCache::init(QStringList list) {
    // also should free memory
    lock();
    cachedImages->clear();
    for(int i=0; i<list.length(); i++) {
        cachedImages->append(new CacheObject(list.at(i)));
    }
    unlock();
}

void ImageCache::loadAt(int pos) {
    lock();
    cachedImages->at(pos)->load();
    unlock();
}

Image* ImageCache::imageAt(int pos) {
    return cachedImages->at(pos)->image();
}

void ImageCache::readSettings() {
    lock();
    maxCacheSize = globalSettings->s.value("cacheSize").toInt();
    unlock();
}

void ImageCache::applySettings() {
    readSettings();
    //shrinkTo(maxCacheSize);
}

void ImageCache::lock() {
    mutex.lock();
}

void ImageCache::unlock() {
    mutex.unlock();
}

ImageCache::~ImageCache() {

}
