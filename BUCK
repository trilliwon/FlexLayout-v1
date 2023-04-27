# Copyright (c) 2014-present, Facebook, Inc.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

load("//:pilates_defs.bzl", "LIBRARY_COMPILER_FLAGS", "BASE_COMPILER_FLAGS", "GTEST_TARGET", "pilates_dep", "cxx_library", "cxx_test")

GMOCK_OVERRIDE_FLAGS = [
    # gmock does not mark mocked methods as override, ignore the warnings in tests
    "-Wno-inconsistent-missing-override",
]

COMPILER_FLAGS = LIBRARY_COMPILER_FLAGS + [
    "-std=c++1y",
]

TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + [
    "-std=c++1y",
]

cxx_library(
    name = "pilates",
    srcs = glob(["Sources/pilates/*.cpp"]),
    header_namespace = "pilates",
    exported_headers = subdir_glob([("Sources/pilates", "*.h")]),
    compiler_flags = COMPILER_FLAGS,
    soname = "libpilatescore.$(ext)",
    tests = [":PilatesTests"],
    visibility = ["PUBLIC"],
    deps = [
        pilates_dep("lib/fb:ndklog"),
    ],
)

cxx_test(
    name = "PilatesTests",
    srcs = glob(["core-tests/*.cpp"]),
    compiler_flags = TEST_COMPILER_FLAGS,
    contacts = ["emilsj@fb.com"],
    visibility = ["PUBLIC"],
    deps = [
        ":pilates",
        GTEST_TARGET,
    ],
)
