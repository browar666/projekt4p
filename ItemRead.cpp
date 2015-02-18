#include <iostream>
#include <string>
#include "tinyxml/tinyxml.h"

int main()
{
	TiXmlDocument doc("items.xml");
	if(!doc.LoadFile())
		return 6;
	TiXmlElement *items = doc.FirstChildElement("items");
	int i =0;
	TiXmlElement *item = items->FirstChildElement("item");
	while(item)
	{
		++i;
		printf("%i\n",i);
		item = item->NextSiblingElement("item");
	}
}
