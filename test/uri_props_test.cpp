#include <gtest/gtest.h>
#include <nova/uri.h>

using namespace nova;

TEST(props_test, mail_uri_props_test)
{
    URI uri{"mailto:mduerst@ifi.unizh.ch"};
    ASSERT_TRUE(uri.is_absolute());
    ASSERT_TRUE(uri.is_opaque());
}

TEST(props_test, news_uri_props_test)
{
    URI uri{"news:comp.lang.java"};
    ASSERT_TRUE(uri.is_absolute());
    ASSERT_TRUE(uri.is_opaque());
}

TEST(props_test, http_uri_props_test)
{
    URI uri{"http://localhost"};
    ASSERT_TRUE(uri.is_absolute());
    ASSERT_TRUE(!uri.is_opaque());
}
