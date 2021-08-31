/*
 * libxml2 example
 * (C) Copyright 2016, Wasion Group
 * YuWeifeng, <yuweifeng@wasion.com>
 *
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

static char xml_file[PATH_MAX] = "util.xml";
static xmlDocPtr xml_doc = NULL;
static xmlNodePtr node_root = NULL;

static void init_xml_file(void)
{
	xmlNodePtr node = NULL;

	/* a node and set it as a root node */
	node_root = xmlNewNode(NULL, BAD_CAST "wasion");
	xmlDocSetRootElement(xml_doc, node_root);

	node = xmlNewChild(node_root, NULL, BAD_CAST "copyright", NULL);
	xmlNewProp(node, BAD_CAST "author", BAD_CAST "pengshuiming");
	xmlNewProp(node, BAD_CAST "version", BAD_CAST "1.0.0");

	/* Init libxml */
	xmlInitParser();
}

static xmlXPathObjectPtr get_xpath_object(xmlDocPtr doc, const char* key)
{
	xmlXPathContextPtr context = xmlXPathNewContext(doc);
	if (!context)
		return NULL;

	xmlChar *xml_key = xmlCharStrdup(key);
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xml_key, context);
	xmlFree(xml_key);

	xmlXPathFreeContext(context);

	if (!result)
		return NULL;

	if (!result || xmlXPathNodeSetIsEmpty(result->nodesetval))
		return NULL;

	return result;
}

static void set_node_value(xmlNode* node, const char *value)
{
	xmlChar *xml_value = xmlCharStrdup(value);
	xmlNodeSetContent(node, xml_value);
	xmlFree(xml_value);
}

static void set_attr_value(xmlNode* node, const char *attr_name, const char *value)
{
	xmlChar *xml_prop_name = xmlCharStrdup(attr_name);
	xmlChar *xml_prop_value = xmlCharStrdup(value);
	xmlSetProp(node, xml_prop_name, xml_prop_value);
	xmlFree(xml_prop_value);
	xmlFree(xml_prop_name);
}


int add_xml_node(const char *parent, const char *name, const char *value)
{
	xmlXPathObjectPtr result = get_xpath_object(xml_doc, parent);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];
	xmlNewChild(first, NULL, BAD_CAST name, BAD_CAST value);

	xmlXPathFreeObject(result);

	return 0;
}

int add_xml_node_attr(const char *node, const char *attr_name, const char *value)
{
	xmlXPathObjectPtr result = get_xpath_object(xml_doc, node);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];
	xmlNewProp(first, BAD_CAST attr_name, BAD_CAST value);

	xmlXPathFreeObject(result);

	return 0;
}

int del_xml_node(const char *key)
{
	xmlXPathObjectPtr result = get_xpath_object(xml_doc,key);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];

	xmlUnlinkNode(first);
	xmlFreeNode(first);

	xmlXPathFreeObject(result);

	return 0;
}

int del_xml_node_attr(const char *node, const char *attr_name)
{
	int ret = 0;

	xmlXPathObjectPtr result = get_xpath_object(xml_doc, node);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];
	xmlAttrPtr attr = xmlHasProp(first, BAD_CAST attr_name);
	if (attr)
		ret = xmlRemoveProp(attr);

	xmlXPathFreeObject(result);

	return ret;
}

int set_xml_node_value(const char *key, const char *value)
{
	int i = 0;

	xmlXPathObjectPtr result = get_xpath_object(xml_doc, key);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	for (i = 0; i < nodeset->nodeNr; i++)
		set_node_value(nodeset->nodeTab[i], value);

	xmlXPathFreeObject(result);

	return 0;
}

int set_xml_node_attr(const char *key, const char *attr_name, const char *value)
{
	int i = 0;

	xmlXPathObjectPtr result = get_xpath_object(xml_doc, key);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	for (i = 0; i < nodeset->nodeNr; i++)
		set_attr_value(nodeset->nodeTab[i], attr_name, value);

	xmlXPathFreeObject(result);

	return 0;
}

int get_xml_node_value(const char *key, char *value)
{
	xmlXPathObjectPtr result = get_xpath_object(xml_doc,key);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];
	xmlChar *xml_value = xmlNodeGetContent(first);
	memcpy(value, xml_value, xmlStrlen(xml_value));
	xmlFree(xml_value);

	xmlXPathFreeObject(result);

	return 0;
}

int get_xml_node_attr_value(const char *node, const char *attr_name, char *value)
{
	xmlXPathObjectPtr result = get_xpath_object(xml_doc, node);
	if (!result)
		return -1;

	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlNodePtr first = nodeset->nodeTab[0];

	xmlChar *xml_prop_name = xmlCharStrdup(attr_name);
	xmlChar *xml_prop_value = xmlGetProp(first, xml_prop_name);
	memcpy(value, xml_prop_value, xmlStrlen(xml_prop_value));
	xmlFree(xml_prop_value);
	xmlFree(xml_prop_name);

	xmlXPathFreeObject(result);

	return 0;
}

/* open xml file */
int open_xml_file(char *fname)
{
	FILE *fp = NULL;

	LIBXML_TEST_VERSION;

	if (fname) {
		memset(xml_file, 0, PATH_MAX);
//		printf("%s %s\n", xml_file, fname);
		memcpy(xml_file, fname, strlen(fname));
//		printf("%s\n", xml_file);
	}

	xmlKeepBlanksDefault(0);
	xmlIndentTreeOutput = 1;

	fp = fopen(xml_file, "r+b");
	if (fp != NULL) {
		/* parse the file and get the DOM */
		xml_doc = xmlReadFd(fp->_fileno, NULL, NULL, 0);
	} else {
		printf("file %s is not exist, create it\n", xml_file);
		/* Creates a new document */
		xml_doc = xmlNewDoc(BAD_CAST "1.0");
	}
	if (xml_doc == NULL) {
		fprintf(stderr, "ERROR: Failed to create/read file %s\n", xml_file);
		return -1;
	}

	if (fp == NULL) {
		init_xml_file();
	} else {
		fclose(fp);
		fp = NULL;

		node_root = xmlDocGetRootElement(xml_doc);
		if (node_root == NULL) {
			printf("%s is empty document, init\n", xml_file);

			init_xml_file();
		}
	}

	return 0;
}

void close_xml_file(void)
{
	/* Dumping document to file */
	xmlSaveFormatFileEnc(xml_file, xml_doc, "UTF-8", 1);

	if (node_root == NULL) {
		xmlFreeNode(node_root);
		node_root = NULL;
	}

	/*free the document */
	if (xml_doc) {
		xmlFreeDoc(xml_doc);
		xml_doc = NULL;
	}

	/* Free the global variables */
	xmlCleanupParser();

	/* this is to debug memory for regression tests */
	xmlMemoryDump();
}
