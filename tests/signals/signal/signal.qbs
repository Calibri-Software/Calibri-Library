import qbs

Product {
    name: "SignalTest"
    targetName: "tst_signal"
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
    cpp.cxxFlags: project.compilerFlags
}
