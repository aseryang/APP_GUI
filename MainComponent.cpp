/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "BinaryData.h"
#include "yylist.h"

//==============================================================================
//==============================================================================
class XmlTreeItem  : public TreeViewItem
{
public:
	XmlTreeItem (XmlElement& x)  : xml (x)
	{
	}

	String getUniqueName() const override
	{
		if (xml.getTagName().isEmpty())
			return "unknown";

		return xml.getTagName();
	}

	bool mightContainSubItems() override
	{
		return xml.getFirstChildElement() != nullptr;
	}

	void paintItem (Graphics& g, int width, int height) override
	{
		// if this item is selected, fill it with a background colour..
		if (isSelected())
			g.fillAll (Colours::blue.withAlpha (0.3f));

		// use a "colour" attribute in the xml tag for this node to set the text colour..
		g.setColour (Colour::fromString (xml.getStringAttribute ("colour", "ff000000")));
		g.setFont (height * 0.7f);

		// draw the xml element's tag name..
		g.drawText (xml.getTagName(),
			4, 0, width - 4, height,
			Justification::centredLeft, true);
	}

	void itemOpennessChanged (bool isNowOpen) override
	{
		if (isNowOpen)
		{
			// if we've not already done so, we'll now add the tree's sub-items. You could
			// also choose to delete the existing ones and refresh them if that's more suitable
			// in your app.
			if (getNumSubItems() == 0)
			{
				// create and add sub-items to this node of the tree, corresponding to
				// each sub-element in the XML..

				forEachXmlChildElement (xml, child)
				{
					jassert (child != nullptr);
					addSubItem (new XmlTreeItem (*child));
				}
			}
		}
		else
		{
			// in this case, we'll leave any sub-items in the tree when the node gets closed,
			// though you could choose to delete them if that's more appropriate for
			// your application.
		}
	}

private:
	XmlElement& xml;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XmlTreeItem)
};

MainContentComponent::MainContentComponent():codeDocumentComponent (codeDocument, nullptr)
{
    setSize (800, 600);
	addAndMakeVisible (codeDocumentComponent);
	codeDocument.addListener (this);
	codeDocument.replaceAllContent (BinaryData::treedemo_xml); 
	parsedXml = nullptr;

	XmlDocument doc (codeDocument.getAllContent());
	parsedXml = doc.getDocumentElement();


	XmlTreeItem* pTree = new XmlTreeItem (*parsedXml);
	resultsTree.setRootItem (pTree);

	addAndMakeVisible (resultsTree);
	resultsTree.setColour (TreeView::backgroundColourId, Colours::white);
	resultsTree.setDefaultOpenness (true);

	gameRooms = new PropertiesDemo();
	addAndMakeVisible(gameRooms);

	gamerInfo = new DemoTabbedComponent();
	addAndMakeVisible(gamerInfo);
	LookAndFeel* p = new LookAndFeel_V2();
	setLookAndFeel(p);
	
	//getLookAndFeel().setUsingNativeAlertWindows (false);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
//     g.fillAll (Colour (0xff001F36));
// 
//     g.setFont (Font (16.0f));
//     g.setColour (Colours::white);
//     g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
	Rectangle<int> area;
	area.setX(0);
	area.setY(0);
	area.setWidth(200);
	area.setHeight(595);
	gameRooms->resized();
	gameRooms->setBounds(area);
	area.setX(595);
	area.setY(0);
	area.setWidth(200);
	area.setHeight(595);
	gamerInfo->setBounds(area);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	Rectangle<int> area (getLocalBounds());
// 	codeDocumentComponent.setBounds (area.removeFromTop(area.getHeight() / 2).reduced (8));
	//resultsTree.setBounds (area);
	
}
