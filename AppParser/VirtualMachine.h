#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "tinyxml/tinyxml.h"

namespace VirtualMachine
{

	struct Node
	{
		WCHAR machinePath[MAX_PATH];
		WCHAR machineName[MAX_PATH];
		Node* next;
	};

	inline Node* NewNode()
	{
		Node* node = new Node;
		ZeroMemory(node, sizeof(Node));
		return node;
	}

	inline void AddNode(Node* &head, Node* node)
	{
		if ( NULL == head )
			head = node;
		else
		{
			node->next = head->next;
			head->next = node;
		}
	}

	inline void DeleteList(Node* node)
	{
		while ( node )
		{
			Node* temp = node;
			node = node->next;
			delete temp;
		}
	}

	inline Node* GetMachineList(const wchar_t* config)
	{
		char configPath[MAX_PATH] = {0};
		WideCharToMultiByte(CP_ACP, NULL, config, -1, configPath, MAX_PATH, NULL, NULL);

		TiXmlDocument xml(configPath);
		xml.LoadFile();

		const TiXmlElement* node = xml.RootElement()->FirstChildElement("Global");

		if ( NULL == node )
			return NULL;

		node = node->FirstChildElement("MachineRegistry");

		if ( NULL == node )
			return NULL;

		node = node->FirstChildElement("MachineEntry");

		if ( NULL == node )
			return NULL;

		Node* head = NULL;

		while ( node )
		{
			Node* data = NewNode();
			const char* value = node->Attribute("src");
			MultiByteToWideChar(CP_UTF8, NULL, value, -1, data->machinePath, MAX_PATH);
			wsprintfW(data->machineName, L"Genymotion - %s", wcsrchr(data->machinePath, L'\\')+1);
			data->machineName[wcslen(data->machineName)-5] = '\0';
			AddNode(head, data);
			node = node->NextSiblingElement();
		}

		return head;
	}

}

#endif // VIRTUALMACHINE_H