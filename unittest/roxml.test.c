
#include "unittest.h"		
#include "../roxml-internal.h"

int test_load_doc(void)
{
	INIT /* init context macro */

	node_t *root = roxml_load_doc("roxml.test.xml");
	ASSERT_NOT_NULL(root);
	
	roxml_close(root);

	root = roxml_load_doc("empty.test.xml");
	ASSERT_NULL(root);
	
	RETURN /* close context macro */
}

int test_tree_on_doc(void)
{
	INIT /* init context macro */

	node_t *root = roxml_load_doc("roxml.test.xml");
	
	ASSERT_NOT_NULL(root);

	ASSERT_NOT_NULL(root->chld); // node0
	ASSERT_NOT_NULL(root->chld->chld);	// node1
	ASSERT_NOT_NULL(root->chld->chld->sibl);	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->sibl);	// node7
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld);	//node3
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl);	//node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl);	//node5
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld);	//node6
	ASSERT_NULL(root->chld->chld->sibl->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->sibl);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->chld);
	ASSERT_NULL(root->sibl);

	// node0
	ASSERT_NULL(root->chld->attr)

	// node1
	ASSERT_NOT_NULL(root->chld->chld->attr)
	ASSERT_NOT_NULL(root->chld->chld->attr->sibl)
	ASSERT_NULL(root->chld->chld->attr->sibl->sibl)

	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->attr->sibl->sibl)

	// node3
	ASSERT_NULL(root->chld->chld->sibl->chld->attr)

	// node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl->sibl)

	// node5
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->attr)

	// node6
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->attr)

	// node7
	ASSERT_NULL(root->chld->chld->sibl->sibl->attr)

	// node0
	ASSERT_NOT_NULL(root->chld->text)
	ASSERT_NOT_NULL(root->chld->text->sibl)
	ASSERT_NOT_NULL(root->chld->text->sibl->sibl)
	ASSERT_NOT_NULL(root->chld->text->sibl->sibl->sibl)
	ASSERT_NULL(root->chld->text->sibl->sibl->sibl->sibl)

	// node1
	ASSERT_NOT_NULL(root->chld->chld->text)
	ASSERT_NULL(root->chld->chld->text->sibl)

	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->text)
	ASSERT_NOT_NULL(root->chld->chld->sibl->text->sibl)
	ASSERT_NOT_NULL(root->chld->chld->sibl->text->sibl->sibl)
	ASSERT_NOT_NULL(root->chld->chld->sibl->text->sibl->sibl->sibl)
	ASSERT_NULL(root->chld->chld->sibl->text->sibl->sibl->sibl->sibl)

	// node3
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->text)
	ASSERT_NULL(root->chld->chld->sibl->chld->text->sibl)

	// node4
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->text)

	// node5
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->text)
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->text->sibl)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->text->sibl->sibl)

	// node6
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->text)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->text->sibl)

	// node7
	ASSERT_NOT_NULL(root->chld->chld->sibl->sibl->text)
	ASSERT_NULL(root->chld->chld->sibl->sibl->text->sibl)

	roxml_close(root);

	RETURN /* close context macro */
}

int test_names_on_doc(void)
{
	INIT /* init context macro */

	char string[128];
	node_t *root = roxml_load_doc("roxml.test.xml");
	
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld, NULL, 0), "node0"); // node0
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld, NULL, 0), "node1");	// node1
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl, NULL, 0), "node2");	// node2
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->sibl, NULL, 0), "node7");	// node7
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld, NULL, 0), "node3");	//node3
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl, NULL, 0), "node4");	//node4
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl, NULL, 0), "node5");	//node5
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl->chld, NULL, 0), "node6");	//node6

	ASSERT_NULL(roxml_get_name(root->chld->attr, NULL, 0))

	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, NULL, 0), "value")

	ASSERT_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, string, 128), string)
	ASSERT_STRING_EQUAL(string, "value")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN /* close context macro */
}

int test_load_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	}

	node_t *root = roxml_load_buf(buf);
	ASSERT_NOT_NULL(root);
	
	roxml_close(root);

	root = roxml_load_buf(NULL);
	ASSERT_NULL(root);
	
	RETURN /* close context macro */
}

int test_tree_on_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	} else	{
		ASSERT_NOT_NULL(NULL);
		RETURN
	}

	node_t *root = roxml_load_buf(buf);
	
	ASSERT_NOT_NULL(root);

	ASSERT_NOT_NULL(root->chld); // node0
	ASSERT_NOT_NULL(root->chld->chld);	// node1
	ASSERT_NOT_NULL(root->chld->chld->sibl);	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->sibl);	// node7
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld);	//node3
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl);	//node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl);	//node5
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld);	//node6
	ASSERT_NULL(root->chld->chld->sibl->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->sibl);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->chld);
	ASSERT_NULL(root->sibl);

	// node0
	ASSERT_NULL(root->chld->attr)

	// node1
	ASSERT_NOT_NULL(root->chld->chld->attr)
	ASSERT_NOT_NULL(root->chld->chld->attr->sibl)
	ASSERT_NULL(root->chld->chld->attr->sibl->sibl)

	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->attr->sibl->sibl)

	// node3
	ASSERT_NULL(root->chld->chld->sibl->chld->attr)

	// node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl->sibl)

	// node5
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->attr)

	// node6
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->attr)

	// node7
	ASSERT_NULL(root->chld->chld->sibl->sibl->attr)

	roxml_close(root);

	RETURN /* close context macro */
}

int test_names_on_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];
	char string[128];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	}

	node_t *root = roxml_load_buf(buf);
	
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld, NULL, 0), "node0"); // node0
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld, NULL, 0), "node1");	// node1
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl, NULL, 0), "node2");	// node2
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->sibl, NULL, 0), "node7");	// node7
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld, NULL, 0), "node3");	//node3
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl, NULL, 0), "node4");	//node4
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl, NULL, 0), "node5");	//node5
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl->chld, NULL, 0), "node6");	//node6

	ASSERT_NULL(roxml_get_name(root->chld->attr, NULL, 0))

	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, NULL, 0), "value")

	ASSERT_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, string, 128), string)
	ASSERT_STRING_EQUAL(string, "value")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN /* close context macro */
}

int test_load_human_doc(void)
{
	INIT /* init context macro */

	node_t *root = roxml_load_doc("roxml.test.xml.human");
	ASSERT_NOT_NULL(root);
	
	roxml_close(root);

	root = roxml_load_doc("empty.test.xml");
	ASSERT_NULL(root);
	
	RETURN /* close context macro */
}

int test_tree_on_human_doc(void)
{
	INIT /* init context macro */

	node_t *root = roxml_load_doc("roxml.test.xml.human");
	
	ASSERT_NOT_NULL(root);

	ASSERT_NOT_NULL(root->chld); // node0
	ASSERT_NOT_NULL(root->chld->chld);	// node1
	ASSERT_NOT_NULL(root->chld->chld->sibl);	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->sibl);	// node7
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld);	//node3
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl);	//node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl);	//node5
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld);	//node6
	ASSERT_NULL(root->chld->chld->sibl->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->sibl);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->chld);
	ASSERT_NULL(root->sibl);

	// node0
	ASSERT_NULL(root->chld->attr)

	// node1
	ASSERT_NOT_NULL(root->chld->chld->attr)
	ASSERT_NOT_NULL(root->chld->chld->attr->sibl)
	ASSERT_NULL(root->chld->chld->attr->sibl->sibl)

	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->attr->sibl->sibl)

	// node3
	ASSERT_NULL(root->chld->chld->sibl->chld->attr)

	// node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl->sibl)

	// node5
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->attr)

	// node6
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->attr)

	// node7
	ASSERT_NULL(root->chld->chld->sibl->sibl->attr)

	roxml_close(root);

	RETURN /* close context macro */
}

int test_names_on_human_doc(void)
{
	INIT /* init context macro */

	char string[128];
	node_t *root = roxml_load_doc("roxml.test.xml.human");
	
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld, NULL, 0), "node0"); // node0
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld, NULL, 0), "node1");	// node1
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl, NULL, 0), "node2");	// node2
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->sibl, NULL, 0), "node7");	// node7
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld, NULL, 0), "node3");	//node3
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl, NULL, 0), "node4");	//node4
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl, NULL, 0), "node5");	//node5
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl->chld, NULL, 0), "node6");	//node6

	ASSERT_NULL(roxml_get_name(root->chld->attr, NULL, 0))

	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, NULL, 0), "value")

	ASSERT_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, string, 128), string)
	ASSERT_STRING_EQUAL(string, "value")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN /* close context macro */
}

int test_load_human_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml.human", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	}

	node_t *root = roxml_load_buf(buf);
	ASSERT_NOT_NULL(root);
	
	roxml_close(root);

	root = roxml_load_buf(NULL);
	ASSERT_NULL(root);
	
	RETURN /* close context macro */
}

int test_tree_on_human_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml.human", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	}

	node_t *root = roxml_load_buf(buf);
	
	ASSERT_NOT_NULL(root);

	ASSERT_NOT_NULL(root->chld); // node0
	ASSERT_NOT_NULL(root->chld->chld);	// node1
	ASSERT_NOT_NULL(root->chld->chld->sibl);	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->sibl);	// node7
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld);	//node3
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl);	//node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl);	//node5
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld);	//node6
	ASSERT_NULL(root->chld->chld->sibl->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->sibl);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->chld);
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->sibl->sibl->sibl);
	ASSERT_NULL(root->chld->chld->chld);
	ASSERT_NULL(root->sibl);

	// node0
	ASSERT_NULL(root->chld->attr)

	// node1
	ASSERT_NOT_NULL(root->chld->chld->attr)
	ASSERT_NOT_NULL(root->chld->chld->attr->sibl)
	ASSERT_NULL(root->chld->chld->attr->sibl->sibl)

	// node2
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->attr->sibl->sibl)

	// node3
	ASSERT_NULL(root->chld->chld->sibl->chld->attr)

	// node4
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr)
	ASSERT_NOT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl)
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->attr->sibl->sibl)

	// node5
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->attr)

	// node6
	ASSERT_NULL(root->chld->chld->sibl->chld->sibl->sibl->chld->attr)

	// node7
	ASSERT_NULL(root->chld->chld->sibl->sibl->attr)

	roxml_close(root);

	RETURN /* close context macro */
}

int test_names_on_human_buf(void)
{
	INIT /* init context macro */

	FILE * doc = NULL;
	char buf[2048];
	char string[128];

	memset(buf, 0, sizeof(char)*2048);
	doc = fopen("roxml.test.xml.human", "r");
	
	ASSERT_NOT_NULL(doc)
	if(doc)	{
		fread(buf, 2048, 1, doc);
		fclose(doc);
	}

	node_t *root = roxml_load_buf(buf);
	
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld, NULL, 0), "node0"); // node0
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld, NULL, 0), "node1");	// node1
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl, NULL, 0), "node2");	// node2
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->sibl, NULL, 0), "node7");	// node7
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld, NULL, 0), "node3");	//node3
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl, NULL, 0), "node4");	//node4
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl, NULL, 0), "node5");	//node5
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->sibl->chld, NULL, 0), "node6");	//node6

	ASSERT_NULL(roxml_get_name(root->chld->attr, NULL, 0))

	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->attr->sibl, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, NULL, 0), "value")

	ASSERT_EQUAL(roxml_get_name(root->chld->chld->sibl->chld->sibl->attr->sibl, string, 128), string)
	ASSERT_STRING_EQUAL(string, "value")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN /* close context macro */
}

int test_prev_next(void)
{
	INIT /* init context macro */

	node_t *root = roxml_load_doc("roxml.test.xml");
	
	node_t *node0 = root->chld;
	node_t *node1 = root->chld->chld;
	node_t *node2 = root->chld->chld->sibl;
	node_t *node3 = root->chld->chld->sibl->chld;
	node_t *node4 = root->chld->chld->sibl->chld->sibl;
	node_t *node5 = root->chld->chld->sibl->chld->sibl->sibl;
	node_t *node6 = root->chld->chld->sibl->chld->sibl->sibl->chld;
	node_t *node7 = root->chld->chld->sibl->sibl;

	ASSERT_STRING_EQUAL(roxml_get_name(node0->prev, NULL, 0), "root");
	ASSERT_STRING_EQUAL(roxml_get_name(node1->next, NULL, 0), "node2");
	ASSERT_STRING_EQUAL(roxml_get_name(node1->prev, NULL, 0), "node0");
	ASSERT_STRING_EQUAL(roxml_get_name(node2->next, NULL, 0), "node7");
	ASSERT_STRING_EQUAL(roxml_get_name(node2->prev, NULL, 0), "node1");
	ASSERT_STRING_EQUAL(roxml_get_name(node3->next, NULL, 0), "node4");
	ASSERT_STRING_EQUAL(roxml_get_name(node3->prev, NULL, 0), "node2");
	ASSERT_STRING_EQUAL(roxml_get_name(node4->next, NULL, 0), "node5");
	ASSERT_STRING_EQUAL(roxml_get_name(node4->prev, NULL, 0), "node3");
	ASSERT_STRING_EQUAL(roxml_get_name(node5->next, NULL, 0), "node7");
	ASSERT_STRING_EQUAL(roxml_get_name(node5->prev, NULL, 0), "node4");
	ASSERT_STRING_EQUAL(roxml_get_name(node6->next, NULL, 0), "node7");
	ASSERT_STRING_EQUAL(roxml_get_name(node6->prev, NULL, 0), "node5");
	ASSERT_STRING_EQUAL(roxml_get_name(node7->prev, NULL, 0), "node6");
	ASSERT_NULL(node0->next);
	ASSERT_NULL(node7->next);

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN /* close context macro */
}

int test_malloc_release(void)
{
	INIT /* init context macro */

	roxml_release(RELEASE_ALL);
	ASSERT_NULL(head_cell.next);

	memory_cell_t *ptr = &head_cell;
	char * ptr1 = roxml_malloc(1, 10, PTR_CHAR);
	char * ptr2 = roxml_malloc(1, 10, PTR_CHAR);
	char * ptr3 = roxml_malloc(1, 10, PTR_CHAR);
	char * ptr4 = roxml_malloc(1, 10, PTR_CHAR);

	ASSERT_EQUAL(ptr->next->ptr, ptr1);
	ASSERT_EQUAL(ptr->next->next->ptr, ptr2);
	ASSERT_EQUAL(ptr->next->next->next->ptr, ptr3);
	ASSERT_EQUAL(ptr->next->next->next->next->ptr, ptr4);
	ASSERT_NULL(ptr->next->next->next->next->next);

	roxml_release(ptr4);
	ptr = head_cell.next;
	while(ptr)	{
		ASSERT_NOT_EQUAL(ptr->ptr, ptr4);
		ptr = ptr->next;
	}

	roxml_release(RELEASE_LAST);
	ptr = head_cell.next;
	while(ptr)	{
		ASSERT_NOT_EQUAL(ptr->ptr, ptr3);
		ptr = ptr->next;
	}

	roxml_release(ptr1);
	ptr = head_cell.next;
	while(ptr)	{
		ASSERT_NOT_EQUAL(ptr->ptr, ptr1);
		ptr = ptr->next;
	}

	roxml_release(RELEASE_ALL);
	ASSERT_NULL(head_cell.next);
	roxml_release(RELEASE_ALL);
	ASSERT_NULL(head_cell.next);
	roxml_release(RELEASE_LAST);
	ASSERT_NULL(head_cell.next);

	RETURN /* close context macro */
}

int test_create_node(void)
{
	INIT

	FILE * doc = (FILE *)0x42;
	unsigned int * idx = (unsigned int *)0x43;
	char * buf = (char *)0x44;

	node_t * node = roxml_create_node(1, doc, buf, idx, ROXML_FILE | ROXML_VAL);
	node_t * cnode = roxml_create_node(1, doc, NULL, NULL, ROXML_FILE | ROXML_VAL);
	node_t * anode = roxml_create_node(1, doc, NULL, NULL, ROXML_FILE | ROXML_ARG);
	node_t * close = roxml_create_node(10, doc, NULL, NULL, ROXML_FILE | ROXML_VAL);
	roxml_close_node(node, close);
	ASSERT_EQUAL(node->type, ROXML_FILE | ROXML_VAL)
	ASSERT_EQUAL(node->src.buf, buf)
	ASSERT_EQUAL(node->idx, idx)
	ASSERT_EQUAL(node->pos, 1)
	ASSERT_EQUAL(node->end, 10)
	ASSERT_NULL(node->prnt)
	ASSERT_NULL(node->sibl)
	ASSERT_NULL(node->chld)
	ASSERT_NULL(node->attr)

	roxml_parent_node(cnode, node);
	roxml_parent_node(node, anode);
	ASSERT_EQUAL(node->prnt, cnode)
	ASSERT_EQUAL(anode->prnt, node)
	ASSERT_EQUAL(cnode->chld, node)
	ASSERT_EQUAL(node->attr, anode)

	roxml_parent_node(cnode, node);
	roxml_parent_node(node, anode);
	ASSERT_EQUAL(node->sibl, node)
	ASSERT_EQUAL(anode->sibl, anode)

	roxml_free_node(node);
	roxml_free_node(cnode);
	roxml_free_node(anode);

	RETURN
}

int test_get_chld(void)
{
	INIT
	node_t *root = roxml_load_doc("roxml.test.xml");

	ASSERT_STRING_EQUAL(roxml_get_name(root, NULL, 0), "root")

	node_t * node0 = roxml_get_chld(root, NULL, 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node0, NULL, 0), "node0")
	node_t * node1 = roxml_get_chld(node0, NULL, 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node1, NULL, 0), "node1")
	node_t * node2 = roxml_get_chld(node0, NULL, 1);
	ASSERT_STRING_EQUAL(roxml_get_name(node2, NULL, 0), "node2")
	node_t * node3 = roxml_get_chld(node2, NULL, 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node3, NULL, 0), "node3")
	node_t * node4 = roxml_get_chld(node2, NULL, 1);
	ASSERT_STRING_EQUAL(roxml_get_name(node4, NULL, 0), "node4")
	node_t * node5 = roxml_get_chld(node2, NULL, 2);
	ASSERT_STRING_EQUAL(roxml_get_name(node5, NULL, 0), "node5")
	node_t * node6 = roxml_get_chld(node5, NULL, 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node6, NULL, 0), "node6")
	node_t * node7 = roxml_get_chld(node0, NULL, 2);
	ASSERT_STRING_EQUAL(roxml_get_name(node7, NULL, 0), "node7")

	node0 = roxml_get_chld(root, "node0", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node0, NULL, 0), "node0")
	node1 = roxml_get_chld(node0,"node1", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node1, NULL, 0), "node1")
	node2 = roxml_get_chld(node0, "node2", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node2, NULL, 0), "node2")
	node3 = roxml_get_chld(node2, "node3", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node3, NULL, 0), "node3")
	node4 = roxml_get_chld(node2, "node4", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node4, NULL, 0), "node4")
	node5 = roxml_get_chld(node2, "node5", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node5, NULL, 0), "node5")
	node6 = roxml_get_chld(node5, "node6", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node6, NULL, 0), "node6")
	node7 = roxml_get_chld(node0, "node7", 0);
	ASSERT_STRING_EQUAL(roxml_get_name(node7, NULL, 0), "node7")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN
}

int test_get_chld_nb(void)
{
	INIT

	node_t *root = roxml_load_doc("roxml.test.xml");

	int nb = roxml_get_chld_nb(root);	// root
	ASSERT_EQUAL(nb, 1);
	nb = roxml_get_chld_nb(root->chld);	// node0
	ASSERT_EQUAL(nb, 3);
	nb = roxml_get_chld_nb(root->chld->chld);	// node1
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_chld_nb(root->chld->chld->sibl);	// node2
	ASSERT_EQUAL(nb, 3);
	nb = roxml_get_chld_nb(root->chld->chld->sibl->sibl);	// node7
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_chld_nb(root->chld->chld->sibl->chld); // node3
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_chld_nb(root->chld->chld->sibl->chld->sibl);	// node4
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_chld_nb(root->chld->chld->sibl->chld->sibl->sibl);	// node5
	ASSERT_EQUAL(nb, 1);
	nb = roxml_get_chld_nb(root->chld->chld->sibl->chld->sibl->sibl->chld);	// node6
	ASSERT_EQUAL(nb, 0);

	roxml_close(root);

	RETURN
}

int test_get_content(void)
{
	INIT
	node_t *root = roxml_load_doc("roxml.test.xml");
	
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld, NULL, 0), ""); // node0
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld, NULL, 0), "text1");	// node1
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl, NULL, 0), "");	// node2
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->sibl, NULL, 0), "\"<node8>\"");	// node7
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld, NULL, 0), "text2");	//node3
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld->sibl, NULL, 0), "");	//node4
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld->sibl->sibl, NULL, 0), "text3text4");	//node5
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld->sibl->sibl->chld, NULL, 0), "text5");	//node6

	ASSERT_NULL(roxml_get_content(root->chld->attr, NULL, 0))

	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->attr, NULL, 0), "name1")
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->attr->sibl, NULL, 0), "value1")
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->attr, NULL, 0), "name2")
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->attr->sibl, NULL, 0), "value2")
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld->sibl->attr, NULL, 0), "name4")
	ASSERT_STRING_EQUAL(roxml_get_content(root->chld->chld->sibl->chld->sibl->attr->sibl, NULL, 0), "value4")

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN
}

int test_get_attr_nb(void)
{
	INIT
	node_t *root = roxml_load_doc("roxml.test.xml");

	int nb = roxml_get_attr_nb(root);	// root
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_attr_nb(root->chld);	// node0
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_attr_nb(root->chld->chld);	// node1
	ASSERT_EQUAL(nb, 2);
	nb = roxml_get_attr_nb(root->chld->chld->sibl);	// node2
	ASSERT_EQUAL(nb, 2);
	nb = roxml_get_attr_nb(root->chld->chld->sibl->sibl);	// node7
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_attr_nb(root->chld->chld->sibl->chld); // node3
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_attr_nb(root->chld->chld->sibl->chld->sibl);	// node4
	ASSERT_EQUAL(nb, 2);
	nb = roxml_get_attr_nb(root->chld->chld->sibl->chld->sibl->sibl);	// node5
	ASSERT_EQUAL(nb, 0);
	nb = roxml_get_attr_nb(root->chld->chld->sibl->chld->sibl->sibl->chld);	// node6
	ASSERT_EQUAL(nb, 0);

	roxml_close(root);
	RETURN
}

int test_get_attr(void)
{
	INIT

	node_t *root = roxml_load_doc("roxml.test.xml");

	node_t * node0 = roxml_get_chld(root, NULL, 0);
	node_t * node1 = roxml_get_chld(node0, NULL, 0);
	node_t * node2 = roxml_get_chld(node0, NULL, 1);
	node_t * node4 = roxml_get_chld(node2, NULL, 1);

	node_t * attr0 = roxml_get_attr(root, NULL, 0);
	node_t * attr1 = roxml_get_attr(node1, NULL, 0);
	node_t * attr2 = roxml_get_attr(node2, NULL, 0);
	node_t * attr4 = roxml_get_attr(node4, NULL, 0);

	ASSERT_NULL(attr0)
	ASSERT_STRING_EQUAL(roxml_get_name(attr1, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(attr2, NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_name(attr4, NULL, 0), "name")

	attr0 = roxml_get_attr(root, NULL, 1);
	attr1 = roxml_get_attr(node1, NULL, 1);
	attr2 = roxml_get_attr(node2, NULL, 1);
	attr4 = roxml_get_attr(node4, NULL, 1);

	ASSERT_NULL(attr0)
	ASSERT_STRING_EQUAL(roxml_get_name(attr1, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(attr2, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(attr4, NULL, 0), "value")

	attr0 = roxml_get_attr(root, "value", 0);
	attr1 = roxml_get_attr(node1, "value", 0);
	attr2 = roxml_get_attr(node2, "value", 0);
	attr4 = roxml_get_attr(node4, "value", 0);

	ASSERT_NULL(attr0)
	ASSERT_STRING_EQUAL(roxml_get_name(attr1, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(attr2, NULL, 0), "value")
	ASSERT_STRING_EQUAL(roxml_get_name(attr4, NULL, 0), "value")

	attr0 = roxml_get_attr(root, NULL, 2);
	attr1 = roxml_get_attr(node1, NULL, 2);
	attr2 = roxml_get_attr(node2, NULL, 2);
	attr4 = roxml_get_attr(node4, NULL, 2);

	ASSERT_NULL(attr0)
	ASSERT_NULL(attr1)
	ASSERT_NULL(attr2)
	ASSERT_NULL(attr4)

	attr1 = roxml_get_attr(node1, "toto", 0);
	ASSERT_NULL(attr1)

	roxml_release(RELEASE_ALL);
	roxml_close(root);

	RETURN
}

int test_parse_xpath(void)
{
	INIT

	xpath_node_t *ptr;
	char mypath[128] = "/node[first() or last()]/item/title/@version || /node/item/title[@version < 3] || /node/item/title[@version = v1]";
	int ret = roxml_parse_xpath(mypath, &ptr);	

	ASSERT_EQUAL(ret, 3)
	ASSERT_NULL(ptr[0].axis);
	ASSERT_NULL(ptr[0].cond);
	ASSERT_NOT_NULL(ptr[0].next);
	ASSERT_NOT_NULL(ptr[0].next->next);
	ASSERT_NOT_NULL(ptr[0].next->next->next);
	ASSERT_NOT_NULL(ptr[0].next->next->next->next);
	ASSERT_NULL(ptr[0].next->next->next->next->next);
	ASSERT_STRING_EQUAL(ptr[0].next->axis, "node")
	ASSERT_NOT_NULL(ptr[0].next->cond)
	ASSERT_NOT_NULL(ptr[0].next->cond->next)
	ASSERT_NULL(ptr[0].next->cond->next->next)
	ASSERT_STRING_EQUAL(ptr[0].next->cond->arg1, "first()")
	ASSERT_STRING_EQUAL(ptr[0].next->cond->next->arg1, "last()")
	ASSERT_EQUAL(ptr[0].next->cond->next->func, ROXML_FUNC_LAST)
	ASSERT_EQUAL(ptr[0].next->cond->func, ROXML_FUNC_FIRST)
	ASSERT_EQUAL(ptr[0].next->cond->next->rel, ROXML_OPERATOR_OR)
	ASSERT_STRING_EQUAL(ptr[0].next->next->axis, "item")
	ASSERT_NULL(ptr[0].next->next->cond)
	ASSERT_STRING_EQUAL(ptr[0].next->next->next->axis, "title")
	ASSERT_NULL(ptr[0].next->next->next->cond)
	ASSERT_STRING_EQUAL(ptr[0].next->next->next->next->axis, "@version")
	ASSERT_NULL(ptr[0].next->next->next->next->cond)

	ASSERT_NULL(ptr[1].axis);
	ASSERT_NULL(ptr[1].cond);
	ASSERT_NOT_NULL(ptr[1].next);
	ASSERT_EQUAL(ptr[1].rel, ROXML_OPERATOR_OR)
	ASSERT_NOT_NULL(ptr[1].next->next);
	ASSERT_NOT_NULL(ptr[1].next->next->next);
	ASSERT_NOT_NULL(ptr[1].next->next->next);
	ASSERT_NULL(ptr[1].next->next->next->next);
	ASSERT_STRING_EQUAL(ptr[1].next->axis, "node")
	ASSERT_STRING_EQUAL(ptr[1].next->next->axis, "item")
	ASSERT_NULL(ptr[1].next->next->cond)
	ASSERT_STRING_EQUAL(ptr[1].next->next->next->axis, "title")
	ASSERT_NOT_NULL(ptr[1].next->next->next->cond)
	ASSERT_NULL(ptr[1].next->next->next->cond->next)
	ASSERT_STRING_EQUAL(ptr[1].next->next->next->cond->arg1, "@version")
	ASSERT_STRING_EQUAL(ptr[1].next->next->next->cond->arg2, "3")
	ASSERT_EQUAL(ptr[1].next->next->next->cond->func, ROXML_FUNC_INTCOMP)
	ASSERT_EQUAL(ptr[1].next->next->next->cond->op, ROXML_OPERATOR_INF)

	ASSERT_NULL(ptr[2].axis);
	ASSERT_NULL(ptr[2].cond);
	ASSERT_NOT_NULL(ptr[2].next);
	ASSERT_EQUAL(ptr[2].rel, ROXML_OPERATOR_OR)
	ASSERT_NOT_NULL(ptr[2].next->next);
	ASSERT_NOT_NULL(ptr[2].next->next->next);
	ASSERT_NOT_NULL(ptr[2].next->next->next);
	ASSERT_NULL(ptr[2].next->next->next->next);
	ASSERT_STRING_EQUAL(ptr[2].next->axis, "node")
	ASSERT_STRING_EQUAL(ptr[2].next->next->axis, "item")
	ASSERT_NULL(ptr[2].next->next->cond)
	ASSERT_STRING_EQUAL(ptr[2].next->next->next->axis, "title")
	ASSERT_NOT_NULL(ptr[2].next->next->next->cond)
	ASSERT_NULL(ptr[2].next->next->next->cond->next)
	ASSERT_STRING_EQUAL(ptr[2].next->next->next->cond->arg1, "@version")
	ASSERT_STRING_EQUAL(ptr[2].next->next->next->cond->arg2, "v1")
	ASSERT_EQUAL(ptr[2].next->next->next->cond->func, ROXML_FUNC_STRCOMP)
	ASSERT_EQUAL(ptr[2].next->next->next->cond->op, ROXML_OPERATOR_EQU)

	RETURN
}

int test_xpath(void)
{
	INIT

	int nbans;
	node_t *node0;
	node_t *node2;
	node_t *root = roxml_load_doc("roxml.test.xml");

	node_t **node_set = roxml_xpath(root, "/node0/node2/node3", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node3")

	node_set = roxml_xpath(root, "/node0/node2/node", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(root, "/node0/node2/node31", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(root, "/node0/node2/@name", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[0], NULL, 0), "name2")

	node_set = roxml_xpath(root, "/node0/node2/attribute::name", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "name")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[0], NULL, 0), "name2")

	node_set = roxml_xpath(root, "node0", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node0")

	node_set = roxml_xpath(root, "/node0//node5", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node5")

	node_set = roxml_xpath(root, "/node0//node5/node6", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node6")

	node_set = roxml_xpath(root, "/node0/node2", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node2")
	node2 = node_set[0];

	node_set = roxml_xpath(root, "/child::node0/child::node2/parent::", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node0")

	node_set = roxml_xpath(root, "/child::node0/child::node2", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node2")
	node2 = node_set[0];

	node_set = roxml_xpath(node2, "node3", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node3")

	node_set = roxml_xpath(node2, "//node4", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node4")

	node_set = roxml_xpath(node2, "//node7", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "/node3", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "preceding::node1", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node1")

	node_set = roxml_xpath(node2, "preceding::node7", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "following::node1", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "following::node4", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "ancestor-or-self::node2", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node2")

	node_set = roxml_xpath(node2, "ancestor::node2", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "ancestor::node6", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "ancestor::node1", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(node2, "ancestor::node0", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node0")

	node_set = roxml_xpath(node2, "following::node7", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node7")

	node_set = roxml_xpath(root, "/node4", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(root, "root/node0", &nbans);
	ASSERT_EQUAL(nbans, 0)
	
	node_set = roxml_xpath(root, "node0", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node0")
	node0 = node_set[0];

	node_set = roxml_xpath(node0, "//node0", &nbans);
	ASSERT_EQUAL(nbans, 1)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node0")

	node_set = roxml_xpath(node0, "//node1/@*", &nbans);
	ASSERT_EQUAL(nbans, 2)
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[0], NULL, 0), "name1")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[1], NULL, 0), "value1")

	node_set = roxml_xpath(root, "//*", &nbans);
	ASSERT_EQUAL(nbans, 9)

	node_set = roxml_xpath(root, "*", &nbans);
	ASSERT_EQUAL(nbans, 1)

	node_set = roxml_xpath(node0, "*", &nbans);
	ASSERT_EQUAL(nbans, 3)

	node_set = roxml_xpath(root, "//@name", &nbans);
	ASSERT_EQUAL(nbans, 3)
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[0], NULL, 0), "name1")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[1], NULL, 0), "name2")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[2], NULL, 0), "name4")
	
	roxml_close(root);

	roxml_release(RELEASE_ALL);

	root = roxml_load_doc("roxml.test.xml.multiple");
	ASSERT_NOT_NULL(root)

	node_set = roxml_xpath(root, "node", &nbans);
	ASSERT_EQUAL(nbans, 0)

	node_set = roxml_xpath(root, "//node", &nbans);
	ASSERT_EQUAL(nbans, 5)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[0], NULL, 0), "1")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[1], NULL, 0), "node")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[1], NULL, 0), "2")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[2], NULL, 0), "node")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[2], NULL, 0), "3")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[3], NULL, 0), "node")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[3], NULL, 0), "4")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[4], NULL, 0), "node")
	ASSERT_STRING_EQUAL(roxml_get_content(node_set[4], NULL, 0), "5")

	node_set = roxml_xpath(root, "/node0//node2/node3//node5", &nbans);
	ASSERT_EQUAL(nbans, 3)
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[0], NULL, 0), "node5")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[1], NULL, 0), "node5")
	ASSERT_STRING_EQUAL(roxml_get_name(node_set[2], NULL, 0), "node5")

	roxml_close(root);

	roxml_release(RELEASE_ALL);

	RETURN
}

int test_get_node_type(void)
{
	INIT

	int type;

	node_t * cnode = roxml_create_node(1, NULL, NULL, NULL, ROXML_FILE | ROXML_VAL);
	node_t * anode = roxml_create_node(1, NULL, NULL, NULL, ROXML_FILE | ROXML_ARG);

	type = roxml_get_type(cnode);
	ASSERT_EQUAL(type & ROXML_VAL, ROXML_VAL)
	ASSERT_NOT_EQUAL(type & ROXML_ARG, ROXML_ARG)

	type = roxml_get_type(anode);
	ASSERT_NOT_EQUAL(type & ROXML_VAL, ROXML_VAL)
	ASSERT_EQUAL(type & ROXML_ARG, ROXML_ARG)

	roxml_free_node(cnode);
	roxml_free_node(anode);

	RETURN
}

int test_get_node_index(void)
{
	INIT

	int last;

	node_t *root = roxml_load_doc("roxml.test.xml.multiple");

	node_t * node0 = roxml_get_chld(root, NULL, 0);
	node_t * node = roxml_get_chld(node0, NULL, 0);
	ASSERT_EQUAL(roxml_get_node_index(node, &last), 0)
	ASSERT_EQUAL(last, 4)
	node = roxml_get_chld(node0, NULL, 1);
	ASSERT_EQUAL(roxml_get_node_index(node, &last), 1)
	ASSERT_EQUAL(last, 4)
	node = roxml_get_chld(node0, NULL, 2);
	ASSERT_EQUAL(roxml_get_node_index(node, &last), 2)
	ASSERT_EQUAL(last, 4)
	node = roxml_get_chld(node0, NULL, 3);
	ASSERT_EQUAL(roxml_get_node_index(node, &last), 3)
	ASSERT_EQUAL(last, 4)
	node = roxml_get_chld(node0, NULL, 4);
	ASSERT_EQUAL(roxml_get_node_index(node, &last), 4)
	ASSERT_EQUAL(last, 4)
	
	roxml_close(root);

	RETURN
}

int main(int argc, char ** argv)	{
	INIT /* init context macro */

	TEST_FUNC(test_load_doc) 
	TEST_FUNC(test_tree_on_doc) 
	TEST_FUNC(test_names_on_doc) 
	TEST_FUNC(test_load_buf) 
	TEST_FUNC(test_tree_on_buf) 
	TEST_FUNC(test_names_on_buf) 
	TEST_FUNC(test_load_human_doc) 
	TEST_FUNC(test_tree_on_human_doc) 
	TEST_FUNC(test_names_on_human_doc) 
	TEST_FUNC(test_load_human_buf) 
	TEST_FUNC(test_tree_on_human_buf) 
	TEST_FUNC(test_names_on_human_buf) 
	TEST_FUNC(test_prev_next)
	TEST_FUNC(test_malloc_release) 
	TEST_FUNC(test_create_node)
	TEST_FUNC(test_get_chld)
	TEST_FUNC(test_get_chld_nb)
	TEST_FUNC(test_get_content)
	TEST_FUNC(test_get_attr_nb)
	TEST_FUNC(test_get_attr)
	TEST_FUNC(test_parse_xpath)
	TEST_FUNC(test_xpath)
	TEST_FUNC(test_get_node_type)
	TEST_FUNC(test_get_node_index)

	EXEC_UNITTEST /* exec tests depending on command line option see available options with --help */

	RETURN /* close context macro */
}
