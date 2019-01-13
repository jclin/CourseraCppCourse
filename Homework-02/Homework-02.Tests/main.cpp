#pragma once
#include "pch.h"

namespace Homework { namespace Tests
{
    using namespace testing;

    int main(int argc, char **argv)
    {
      InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
} /* Tests */ } /* Homework */

