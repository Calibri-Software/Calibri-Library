import qbs

Project {
    name: "Tests"
    references: [
        "io/io.qbs",
        "tools/tools.qbs",
        "crypto/crypto.qbs",
        "algorithms/algorithms.qbs",
        "signals/signals.qbs",
        "filesystem/filesystem.qbs"
    ]
}
