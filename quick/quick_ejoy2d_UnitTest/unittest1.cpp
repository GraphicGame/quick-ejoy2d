#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ui/UIEventDispatcher.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace quick_ejoy2d_UnitTest {		
	TEST_CLASS(UnitTest1) {
	public:
		TEST_METHOD(UIEventDispatcher) {
			Logger::WriteMessage("test UIEventDispatcher...");
			
			ui::UIEventDispatcher udp;
			ui::EventListenerCallback *callBack = new ui::EventListenerCallback();
			
			udp.addEventListener("click", callBack);
			
			Assert::AreEqual(udp.hasEventListener("click"), true);
			
			Assert::AreEqual(udp.getEventListenerCount("click"), 1);

			//udp.removeEventListener("click");
			//Assert::AreEqual(udp.getEventListenerCount("click"), 0);
			
			//udp.removeAllEventListener();
			//Assert::AreEqual(udp.getEventListenerCount("click"), 0);

			udp.removeEventListener("click", callBack);
			Assert::AreEqual(udp.getEventListenerCount("click"), 0);
		
			udp.addEventListener("click", callBack);
			
			ui::Event *evt = new ui::Event("click");
			udp.dispatchEvent(evt);
			Assert::AreEqual(callBack->hasCalled(), true);
		}
	};
}