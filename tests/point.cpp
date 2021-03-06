////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.09 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "doctest.h"
#include <utility>
#include "pfs/griotte/point.hpp"

using point = pfs::griotte::point<int>;

SCENARIO("Point constructors") {
    GIVEN("A point") {
        WHEN("created with default constructor") {
            point p;

            THEN("all attributes are zero") {
                REQUIRE(p.x() == 0);
                REQUIRE(p.y() == 0);
            }
        }

        AND_WHEN("created by default copy constructor") {
            point p1;
            point p2{p1};

            THEN("all attributes are zero") {
                REQUIRE(p2.x() == 0);
                REQUIRE(p2.y() == 0);
            }
        }

        AND_WHEN("assigned by default copy assignment operator") {
            point p1;
            point p2;
            p2 = p1;

            THEN("all attributes are zero") {
                REQUIRE(p2.x() == 0);
                REQUIRE(p2.y() == 0);
            }
        }
    }

    GIVEN("A point") {
        WHEN("created with [point (unit_t x, unit_t y)] constructor") {
            point p{10, 20};

            THEN("attributes are set properly") {
                REQUIRE(p.x() == 10);
                REQUIRE(p.y() == 20);
            }
        }

        AND_WHEN("created by copy constructor") {
            point p1{10, 20};
            point p2{p1};

            THEN("attributes are set properly") {
                REQUIRE(p2.x() == 10);
                REQUIRE(p2.y() == 20);
            }
        }

        AND_WHEN("assigned by copy assignment operator") {
            point p1{10, 20};
            point p2;
            p2 = p1;

            THEN("attributes are set properly") {
                REQUIRE(p2.x() == 10);
                REQUIRE(p2.y() == 20);
            }
        }
    }
}

TEST_CASE("Set x and y coordinates") {
    point p;

    p.set_x(10);
    p.set_y(20);

    REQUIRE(p.x() == 10);
    REQUIRE(p.y() == 20);
}

TEST_CASE("Increment x and y coordinates") {
    point p{10, 20};

    p.increment_x(10);
    p.increment_y(20);

    REQUIRE(p.x() == 20);
    REQUIRE(p.y() == 40);

    p.increment_x(-10);
    p.increment_y(-20);

    REQUIRE(p.x() == 10);
    REQUIRE(p.y() == 20);

    p.increment(10, 20);

    REQUIRE(p.x() == 20);
    REQUIRE(p.y() == 40);

    p.increment(-10, -20);

    REQUIRE(p.x() == 10);
    REQUIRE(p.y() == 20);
}

TEST_CASE("Adds and substructs operations") {
    point p{10, 20};
    point p1{10, 20};
    point p2{-10, -20};

    p += p1;

    REQUIRE(p.x() == 20);
    REQUIRE(p.y() == 40);

    p += p2;

    REQUIRE(p.x() == 10);
    REQUIRE(p.y() == 20);

    p -= p2;

    REQUIRE(p.x() == 20);
    REQUIRE(p.y() == 40);

    p -= p1;

    REQUIRE(p.x() == 10);
    REQUIRE(p.y() == 20);
}

TEST_CASE("Multiplies by the given factor") {
    point p;

    p = point{10, 10};
    p *= static_cast<float>(0.35);

    REQUIRE(p.x() == 4);
    REQUIRE(p.y() == 4);

    p = point{10, 10};
    p *= static_cast<float>(0.33);

    REQUIRE(p.x() == 3);
    REQUIRE(p.y() == 3);

    p = point{10, 10};
    p *= static_cast<float>(0.55);

    REQUIRE(p.x() == 6);
    REQUIRE(p.y() == 6);

    p = point{10, 10};
    p *= static_cast<float>(-0.35);

    REQUIRE(p.x() == -4);
    REQUIRE(p.y() == -4);

    p = point{10, 10};
    p *= static_cast<float>(-0.33);

    REQUIRE(p.x() == -3);
    REQUIRE(p.y() == -3);

    p = point{10, 10};
    p *= static_cast<float>(-0.55);

    REQUIRE(p.x() == -6);
    REQUIRE(p.y() == -6);

    p = point{10, 10};
    p *= static_cast<double>(0.35);

    REQUIRE(p.x() == 4);
    REQUIRE(p.y() == 4);

    p = point{10, 10};
    p *= static_cast<double>(0.33);

    REQUIRE(p.x() == 3);
    REQUIRE(p.y() == 3);

    p = point{10, 10};
    p *= static_cast<double>(0.55);

    REQUIRE(p.x() == 6);
    REQUIRE(p.y() == 6);

    p = point{10, 10};
    p *= static_cast<double>(-0.35);

    REQUIRE(p.x() == -4);
    REQUIRE(p.y() == -4);

    p = point{10, 10};
    p *= static_cast<double>(-0.33);

    REQUIRE(p.x() == -3);
    REQUIRE(p.y() == -3);

    p = point{10, 10};
    p *= static_cast<double>(-0.55);

    REQUIRE(p.x() == -6);
    REQUIRE(p.y() == -6);
}

TEST_CASE("Points comparison") {
    REQUIRE(point{10, 10} == point{10, 10});
    REQUIRE(point{10, 10} != point{10, 11});
    REQUIRE(point{10, 10} != point{11, 11});
}
