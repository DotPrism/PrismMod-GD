#include <cocos2d.h>
#include <Geode/DefaultInclude.hpp>
#include <Geode/ui/Popup.hpp>

class TestPopup : public geode::Popup {
protected:
	bool init(std::string const& value);

	void onPopup(cocos2d::CCObject*);
public:
	static TestPopup* create(std::string const& text) {
		auto ret = new TestPopup();
		if (ret->init(text)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
		return nullptr;
	}
};