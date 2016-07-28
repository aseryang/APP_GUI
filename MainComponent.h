/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "yylist.h"
#include "yytable.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
	private CodeDocument::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
	void codeDocumentTextInserted (const String&, int) override     {  }
	void codeDocumentTextDeleted (int, int) override                {  }
private:
	TreeView resultsTree;
	CodeDocument codeDocument;
	ScopedPointer<TreeViewItem> rootItem;
	ScopedPointer<XmlElement> parsedXml;
	CodeEditorComponent codeDocumentComponent;
	PropertiesDemo* gameRooms;
	DemoTabbedComponent* gamerInfo;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
