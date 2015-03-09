import qbs

Project {
    name: "Calibri-Library"
    references: [
        "src/src.qbs",
        "tests/tests.qbs"
    ]

    property string libraryName: qbs.buildVariant === "debug"
                                 ? "calibrid"
                                 : "calibri"
    property string libraryDestinationDirectory: sourceDirectory + "/lib"
    property string binaryDestinationDirectory: sourceDirectory + "/bin"
    property string libraryDirectory: sourceDirectory + "/src"

    property var compilerFlags: {
        if (qbs.toolchain.contains("gcc") || qbs.toolchain.contains("mingw")) {
            if (qbs.buildVariant === "debug") {
                return [
                            "-std=c++11",
                            "-og"
                        ]
            } else {
                return [
                            "-std=c++11",
                            "-o3",
                            "-funroll-loops",
                            "-mtune=native",
                            "-march=native"
                        ]
            }
        }

        return []
    }

    property string opensslIncludeDirectory: qbs.getEnv("OPENSSL_INCLUDE_PATH")
    property string opensslLibraryDirectory: qbs.getEnv("OPENSSL_LIBRARY_PATH")
}
