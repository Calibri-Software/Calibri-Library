import qbs

Product {
    name: "FileSystemEngineTest"
    targetName: "tst_filesystemengine"
    destinationDirectory: project.binaryDestinationDirectory
    consoleApplication: true
    type: [
        "application"
    ]
    files: [
        "*.cpp"
    ]

    Depends {
        name: "Source"
    }

    Depends {
        name: "Qt"
        submodules: [
            "testlib"
        ]
    }

    Depends {
        name: "cpp"
    }

    cpp.includePaths: [
        project.libraryDirectory
    ]
    cpp.libraryPaths: [
        project.libraryDestinationDirectory
    ]
    cpp.dynamicLibraries: [
        project.libraryName
    ]
    cpp.cxxFlags: project.compilerFlags
}
