//
//  PathFollowingBehaviour.hpp
//
//  Created by Manuel Ramon Lopez Torres on 24/11/20.
//

#ifndef PathFollowingBehaviour_hpp
#define PathFollowingBehaviour_hpp

#include "cocos2d.h"



class PathFollowingBehaviour : public cocos2d::Node {
public:
    enum class PathFollowingEventType : unsigned {
        LOOPED,
        GONE_BACK,
        ENDED
    };
    
    typedef std::function<void(PathFollowingEventType)> EventCallback;
    
    PathFollowingBehaviour() :
        path_(nullptr),
        pathDir_(1),
        currentTargetIndex_(0),
        velocity_(cocos2d::Vec2::ZERO),
        speed_(0),
        radius_(20),
        steering_(10),
        loop_(false),
        goBack_(false),
        callback_(nullptr) {};
    
    ~PathFollowingBehaviour();
    
    CREATE_FUNC(PathFollowingBehaviour);
    
    virtual void update(float delta);
    
    CC_PROPERTY(cocos2d::PointArray*, path_, Path)
    CC_SYNTHESIZE(float, speed_, Speed)
    CC_SYNTHESIZE(float, steering_, Steering)
    CC_SYNTHESIZE(bool, loop_, Loop)
    CC_SYNTHESIZE(bool, goBack_, GoBack)
    CC_SYNTHESIZE(float, radius_, Radius)
    CC_SYNTHESIZE(EventCallback, callback_, EventCallback)
    
protected:
    void seek(float delta);
    void launchPathFollowingEvent(PathFollowingEventType type);
    
    long currentTargetIndex_;
    int pathDir_;
    cocos2d::Vec2 velocity_;
};
#endif /* PathFollowingBehaviour_hpp */
