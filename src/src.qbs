import qbs

Product {
    name: "Source"
    targetName: project.libraryName
    destinationDirectory: project.libraryDestinationDirectory
    type: [
        "staticlibrary",
        "dynamiclibrary"
    ]
    files: [
        "*.hpp"
    ]

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
        var libraryPaths = []

        if (project.opensslLibraryDirectory !== undefined)
            libraryPaths.push(project.opensslLibraryDirectory)

        return libraryPaths
    }
    cpp.dynamicLibraries: {
        var dynamicLibraries = []

        if (qbs.targetOS.contains("windows"))
            dynamicLibraries.push("eay32")
        else if (qbs.targetOS.contains("linux"))
            dynamicLibraries.push("crypto")

        return dynamicLibraries
    }
    cpp.cxxFlags: project.compilerFlags

    Group {
        name: "Global"
        prefix: "global/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Io"
        prefix: "io/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Tools"
        prefix: "tools/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Thread"
        prefix: "thread/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Signals"
        prefix: "signals/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Crypto"
        prefix: "crypto/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "Algorithms"
        prefix: "algorithms/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }

    Group {
        name: "FileSystem"
        prefix: "filesystem/"
        files: [
            "*.hpp",
            "*.cpp"
        ]
    }
}
