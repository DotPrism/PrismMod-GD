#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

#include <Geode/binding/GameStatsManager.hpp>

#include <capeling.garage-stats-menu/include/StatsDisplayAPI.h>

#include "TestPopup.hpp"

class $modify(ModdifedMenuLayer, MenuLayer) 
{
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(ModdifedMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		//FLAlertLayer::create("PrismMod", "Hello from my custom mod!", "OK")->show();
		TestPopup::create("Hello from my custom mod!")->show();
	}
};

class $modify(CreatorLayer)
{
	void onChallenge(cocos2d::CCObject* sender)
	{
		CreatorLayer::onChallenge(sender);
		//FLAlertLayer::create("CreatorLayer Hook", "You clicked the Challenge button!", "OK")->show();
		geode::createQuickPopup(
			"CreatorLayer Hook", 
			"You clicked the Challenge button!", 
			"Close", "OK", 
			[](auto, bool btn2) {
				if (btn2) {
					TestPopup::create("CreatorLayer Hook")->show();
				}
			}
		);
	}
};

class $modify(GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init())
			return false;

		auto demonSprite = CCSprite::createWithSpriteFrameName("GJ_demonIcon_001.png");
		demonSprite->setScale(0.25);

		auto statMenu = this->getChildByID("capeling.garage-stats-menu/stats-menu");

		auto myStatItem = StatsDisplayAPI::getNewItem("demons"_spr, demonSprite, GameStatsManager::sharedState()->getStat("5"), 0.8f);

		if (statMenu) {
			statMenu->addChild(myStatItem);
			statMenu->updateLayout();
		}

		return true;
	}
};
