import qbs

Project {
    name: "FileSystem"
    references: [
        "filesystemengine/filesystemengine.qbs",
        "directoryiterator/directoryiterator.qbs",
        "fileinfo/fileinfo.qbs"
    ]
}
