plugins {
    alias(libs.plugins.android.library)
    id("maven-publish")
}

android {
    publishing {
        singleVariant("release")
    }

    namespace = "simple.android.asi"

    compileSdk {
        version = release(36)
    }

    defaultConfig {
        minSdk = 21

        consumerProguardFiles("consumer-rules.pro")
        externalNativeBuild {
            cmake {
                cppFlags("")
            }
        }

        ndk {
            abiFilters.add("armeabi-v7a")
            abiFilters.add("arm64-v8a")
        }
    }

    externalNativeBuild {
        cmake {
            path("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
}

dependencies {
}

afterEvaluate {
    publishing {
        publications {
            create<MavenPublication>("release") {
                from(components["release"])
//                groupId = "com.github.你的GitHub用户名"
//                artifactId = "asi-native"
//                version = "1.0.0"
            }
        }
    }
}

