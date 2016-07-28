#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


static void showBubbleMessage (Component* targetComponent, const String& textToShow)
{
	BubbleMessageComponent* bmc = new BubbleMessageComponent();

	if (Desktop::canUseSemiTransparentWindows())
	{
		bmc->setAlwaysOnTop (true);
		bmc->addToDesktop (0);
	}
	else
	{
		targetComponent->getTopLevelComponent()->addChildComponent (bmc);
	}

	AttributedString text (textToShow);
	text.setJustification (Justification::centred);

	bmc->showAt (targetComponent, text, 2000, true, true);
}