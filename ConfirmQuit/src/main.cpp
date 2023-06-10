#include <Geode/modify/PauseLayer.hpp>
#include <iostream>
using namespace geode::prelude;


class $modify(PauseLayer) {

	bool exit = false;

    void onQuit(CCObject* target) {

		// Workaround Because the PauseLayer::onQuit in createQuickPopup runs the modified function
		if (exit) { 
			// exit = false;
			PauseLayer::onQuit(target);
			return;
		}

		geode::createQuickPopup(
			"Quit?",
			"Are you sure to quit the level?", 
			"No", "Yes",
			[&](auto, bool btn2) {
				if (btn2) {
					exit = true;
					PauseLayer::onQuit(target);
				}
			}
		);
	};
};
