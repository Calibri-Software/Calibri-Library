import qbs

Project {
    name: "Crypto"
    references: [
        "digest/digest.qbs",
        "cipher/cipher.qbs"
    ]
}
