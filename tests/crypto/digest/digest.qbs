import qbs

Product {
    name: "DigestTest"
    targetName: "tst_digest"
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

    cpp.includePaths: {
        var includePaths = [
                    project.libraryDirectory
                ]

        if (project.opensslIncludeDirectory !== undefined)
            includePaths.push(project.opensslIncludeDirectory)

        return includePaths
    }
    cpp.libraryPaths: {
        var libraryPaths = [
                    project.libraryDestinationDirectory
                ]

        if (project.opensslLibraryDirectory !== undefined)
            libraryPaths.push(project.opensslLibraryDirectory)

        return libraryPaths
    }
    cpp.dynamicLibraries: {
        var dynamicLibraries = [
                    project.libraryName
                ]

        if (qbs.targetOS.contains("windows"))
            dynamicLibraries.push("eay32")
        else if (qbs.targetOS.contains("linux"))
            dynamicLibraries.push("crypto")

        return dynamicLibraries
    }
    cpp.cxxFlags: project.compilerFlags
}
