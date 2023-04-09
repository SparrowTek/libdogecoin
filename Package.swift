// swift-tools-version: 5.8

import PackageDescription

let package = Package(
    name: "libdogecoin",
    products: [
        .library(
            name: "libdogecoin",
            targets: ["libdogecoin"]),
    ],
    targets: [
        .target(
            name: "libdogecoin"),
    ]
)
