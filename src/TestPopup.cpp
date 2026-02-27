#include "TestPopup.hpp"
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>

using namespace geode::prelude;

bool TestPopup::init(std::string const& value)
{
	if (!Popup::init(500.f, 280.f))
		return false;

	auto menu = cocos2d::CCMenu::create();
	menu->setContentSize(cocos2d::CCSize(500, 280));

	auto title = Mod::get()->getSettingValue<std::string>("prismmod-title");

	this->setTitle(title);

	auto* buttonSprite = ButtonSprite::create("Test Popup", 60, true, "goldFont.fnt", "GJ_button_04.png", 25, 0.5f);

	auto* popupBtn = CCMenuItemSpriteExtra::create(
		buttonSprite,
		this,
		menu_selector(TestPopup::onPopup)
	);

	popupBtn->setID("magneticprism.prismmod/popup-button");
	popupBtn->setPosition(250, 20);

	menu->addChild(popupBtn);

	auto label = cocos2d::CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
	m_mainLayer->addChildAtPosition(label, geode::Anchor::Center);
	m_mainLayer->addChildAtPosition(menu, geode::Anchor::BottomLeft);

	return true;
}

void TestPopup::onPopup(cocos2d::CCObject*)
{
	FLAlertLayer::create(
		"Title",    // title
		"Hi mom!",  // content
		"OK"        // button
	)->show();
}
