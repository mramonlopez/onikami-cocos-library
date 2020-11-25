//
//  PathFollowingBehaviour.cpp
//
//  Created by Manuel Ramon Lopez Torres on 24/11/20.
//

#include "PathFollowingBehaviour.hpp"

USING_NS_CC;

PathFollowingBehaviour::~PathFollowingBehaviour() {
    CC_SAFE_RELEASE(path_);
}

void PathFollowingBehaviour::update(float delta) {
    if (path_) {
        auto target = path_->getControlPointAtIndex(currentTargetIndex_);
        auto position = this->getPosition();
 
        if (position.distance(target) <= radius_) {
            currentTargetIndex_ += pathDir_;
            
            if (currentTargetIndex_ >= path_->count()) {
                if (goBack_) {
                    pathDir_ *= -1;
                    currentTargetIndex_ += pathDir_;
                    this->launchPathFollowingEvent(PathFollowingEventType::GONE_BACK);
                } else if (loop_) {
                    currentTargetIndex_ = 0;
                    this->launchPathFollowingEvent(PathFollowingEventType::LOOPED);
                } else {
                    currentTargetIndex_ = path_->count() - 1;
                    this->launchPathFollowingEvent(PathFollowingEventType::ENDED);
                }
            }
 
            if (currentTargetIndex_ < 0) {
                if (loop_) {
                    pathDir_ *= -1;
                    currentTargetIndex_ += pathDir_;
                    this->launchPathFollowingEvent(PathFollowingEventType::LOOPED);
                } else {
                    currentTargetIndex_ = 0;
                    this->launchPathFollowingEvent(PathFollowingEventType::ENDED);
                }
            }
        }
        
        this->seek(delta);
    }
}

void PathFollowingBehaviour::seek(float delta) {
    auto target = path_->getControlPointAtIndex(currentTargetIndex_);
    auto position = this->getPosition();
    
    auto desiredVelocity = (target - position).getNormalized() * speed_;
    auto steering = desiredVelocity - velocity_;
    
    if (steering.length() > steering_) {
        steering = steering.getNormalized() * steering_;
    }
    
    velocity_ += steering;
    
    if (velocity_.length() > speed_) {
        velocity_ = velocity_.getNormalized() * speed_;
    }
    
    this->setPosition(position + velocity_ * delta);
}

void PathFollowingBehaviour::setPath(cocos2d::PointArray *var) {
    CC_SAFE_RELEASE(path_);
    
    path_ = var;
    
    CC_SAFE_RETAIN(path_);
}

PointArray* PathFollowingBehaviour::getPath() const {
    return path_;
}

void PathFollowingBehaviour::launchPathFollowingEvent(PathFollowingEventType type) {
    if (callback_) {
        callback_(type);
    }
}
