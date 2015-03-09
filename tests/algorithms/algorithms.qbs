import qbs

Project {
    name: "Algorithms"
    references: [
        "split/split.qbs",
        "trim/trim.qbs",
        "simplify/simplify.qbs",
        "join/join.qbs",
        "upper/upper.qbs",
        "lower/lower.qbs",
        "startswith/startswith.qbs",
        "endswith/endswith.qbs",
        "anyof/anyof.qbs"
    ]
}
