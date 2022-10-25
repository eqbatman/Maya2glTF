#include "externals.h"

#include "Arguments.h"
#include "IndentableStream.h"
#include "MayaException.h"
#include "MeshSemantics.h"
#include "filesystem.h"

namespace flag {
const auto gltfFileExtension = "gfe";
const auto glbFileExtension = "gbe";

const auto outputFolder = "of";
const auto cleanOutputFolder = "cof";

const auto sceneName = "sn";
const auto binary = "glb";
const auto dumpMaya = "dmy";
const auto dumpGLTF = "dgl";
const auto externalTextures = "ext";
const auto copyright = "cpr";
const auto splitMeshAnimation = "sma";
const auto splitByReference = "sbr";
const auto separateAccessorBuffers = "sab";

const auto defaultMaterial = "dm";
const auto colorizeMaterials = "cm";
const auto skipStandardMaterials = "ssm";
const auto skipMaterialTextures = "smt";
const auto force32bitIndices = "i32";
const auto disableNameAssignment = "dnn";
const auto scaleFactor = "sf";
const auto mikkelsenTangentSpace = "mts";
const auto mikkelsenTangentAngularThreshold = "mta";
const auto globalOpacityFactor = "gof";

const auto animationClipName = "acn";
const auto animationClipFrameRate = "afr";
const auto animationClipStartTime = "ast";
const auto animationClipEndTime = "aet";

const auto initialValuesTime = "ivt";

const auto redrawViewport = "rvp";

const auto debugTangentVectors = "dtv";
const auto debugNormalVectors = "dnv";
const auto debugVectorLength = "dvl";

const auto meshPrimitiveAttributes = "mpa";
const auto blendPrimitiveAttributes = "bpa";

const auto skipSkinClusters = "ssc";
const auto skipBlendShapes = "sbs";
const auto ignoreMeshDeformers = "imd";

const auto ignoreSegmentScaleCompensation = "isc";

const auto selectedNodesOnly = "sno";
const auto visibleNodesOnly = "vno";

const auto excludeUnusedTexcoord = "eut";

const auto keepShapeNodes = "ksn";

const auto bakeScalingFactor = "bsf";

const auto forceRootNode = "frn";

const auto forceAnimationChannels = "fac";

const auto forceAnimationSampling = "fas";

const auto detectStepAnimations = "dsa";

const auto hashBufferURIs = "hbu";

const auto dumpAccessorComponents = "dac";

const auto niceBufferURIs = "nbu";

const auto convertUnsupportedImages = "cui";

const auto reportSkewedInverseBindMatrices = "rsb";

const auto clearOutputWindow = "cow";

const auto cameras = "cam";

const auto constantTranslationThreshold = "ctt";
const auto constantRotationThreshold = "crt";
const auto constantScalingThreshold = "cst";
const auto constantWeightsThreshold = "cwt";

const auto posPrecision = "prp";
const auto dirPrecision = "prd";
const auto colPrecision = "prc";
const auto texPrecision = "prt";
const auto sclPrecision = "prs";
const auto matPrecision = "prm";

const auto keepObjectNamespace = "kon";

} // namespace flag

inline const char *getArgTypeName(const MSyntax::MArgType argType) {
    switch (argType) {
    case MSyntax::kNoArg:
        return "flag";
    case MSyntax::kBoolean:
        return "boolean";
    case MSyntax::kLong:
        return "integer";
    case MSyntax::kDouble:
        return "float";
    case MSyntax::kString:
        return "string";
    case MSyntax::kUnsigned:
        return "unsigned";
    case MSyntax::kDistance:
        return "distance";
    case MSyntax::kAngle:;
        return "angle";
    case MSyntax::kTime:
        return "time";
    case MSyntax::kSelectionItem:
        return "selectionItem";
    default:
        return nullptr;
    }
}

SyntaxFactory::SyntaxFactory() {
    auto status = setObjectType(kSelectionList, 1);
    THROW_ON_FAILURE(status);

    useSelectionAsDefault(true);

    std::stringstream ss;
    registerFlag(ss, flag::gltfFileExtension, "gltfFileExtension", kString);
    registerFlag(ss, flag::glbFileExtension, "glbFileExtension", kString);
    registerFlag(ss, flag::outputFolder, "outputFolder", kString);
    registerFlag(ss, flag::cleanOutputFolder, "cleanOutputFolder", kNoArg);
    registerFlag(ss, flag::sceneName, "sceneName", kString);
    registerFlag(ss, flag::scaleFactor, "scaleFactor", kDouble);
    registerFlag(ss, flag::binary, "binary", kNoArg);
    registerFlag(ss, flag::separateAccessorBuffers, "separateAccessorBuffers", kNoArg);
    registerFlag(ss, flag::splitMeshAnimation, "splitMeshAnimation", kNoArg);
    registerFlag(ss, flag::splitByReference, "splitByReference", kNoArg);
    registerFlag(ss, flag::dumpGLTF, "dumpGTLF", kString);
    registerFlag(ss, flag::dumpMaya, "dumpMaya", kString);
    registerFlag(ss, flag::dumpAccessorComponents, "dumpAccessorComponents", kNoArg);
    registerFlag(ss, flag::externalTextures, "externalTextures", kNoArg);
    registerFlag(ss, flag::defaultMaterial, "defaultMaterial", kNoArg);
    registerFlag(ss, flag::colorizeMaterials, "colorizeMaterials", kNoArg);
    registerFlag(ss, flag::skipStandardMaterials, "skipStandardMaterials", kNoArg);
    registerFlag(ss, flag::skipMaterialTextures, "skipMaterialTextures", kNoArg);
    registerFlag(ss, flag::force32bitIndices, "force32bitIndices", kNoArg);
    registerFlag(ss, flag::disableNameAssignment, "disableNameAssignment", kNoArg);
    registerFlag(ss, flag::mikkelsenTangentSpace, "mikkelsenTangentSpace", kNoArg);
    registerFlag(ss, flag::mikkelsenTangentAngularThreshold, "mikkelsenTangentAngularThreshold", kDouble);
    registerFlag(ss, flag::debugNormalVectors, "debugNormalVectors", kNoArg);
    registerFlag(ss, flag::debugTangentVectors, "debugTangentVectors", kNoArg);
    registerFlag(ss, flag::debugVectorLength, "debugVectorLength", kDouble);
    registerFlag(ss, flag::globalOpacityFactor, "globalOpacityFactor", kDouble);
    registerFlag(ss, flag::copyright, "copyright", kString);
    registerFlag(ss, flag::detectStepAnimations, "detectStepAnimations", kLong);

    registerFlag(ss, flag::animationClipFrameRate, "animationClipFrameRate", true, kDouble);
    registerFlag(ss, flag::animationClipName, "animationClipName", true, kString);
    registerFlag(ss, flag::animationClipStartTime, "animationClipStartTime", true, kTime);
    registerFlag(ss, flag::animationClipEndTime, "animationClipEndTime", true, kTime);

    registerFlag(ss, flag::initialValuesTime, "initialValuesTime", kTime);

    registerFlag(ss, flag::meshPrimitiveAttributes, "meshPrimitiveAttributes", kString);
    registerFlag(ss, flag::blendPrimitiveAttributes, "blendPrimitiveAttributes", kString);

    registerFlag(ss, flag::ignoreMeshDeformers, "ignoreMeshDeformers", true, kString);
    registerFlag(ss, flag::skipSkinClusters, "skipSkinClusters", kNoArg);
    registerFlag(ss, flag::skipBlendShapes, "skipBlendShapes", kNoArg);

    registerFlag(ss, flag::redrawViewport, "redrawViewport", kNoArg);

    registerFlag(ss, flag::selectedNodesOnly, "selectedNodesOnly", kNoArg);
    registerFlag(ss, flag::visibleNodesOnly, "visibleNodesOnly", kNoArg);

    registerFlag(ss, flag::excludeUnusedTexcoord, "excludeUnusedTexcoord", kNoArg);

    registerFlag(ss, flag::ignoreSegmentScaleCompensation, "ignoreSegmentScaleCompensation", kNoArg);

    registerFlag(ss, flag::keepShapeNodes, "keepShapeNodes", kNoArg);
    registerFlag(ss, flag::bakeScalingFactor, "bakeScalingFactor", kNoArg);
    registerFlag(ss, flag::forceRootNode, "forceRootNode", kNoArg);
    registerFlag(ss, flag::forceAnimationChannels, "forceAnimationChannels", kNoArg);
    registerFlag(ss, flag::forceAnimationSampling, "forceAnimationSampling", kNoArg);

    registerFlag(ss, flag::hashBufferURIs, "hashBufferURI", kNoArg);
    registerFlag(ss, flag::niceBufferURIs, "niceBufferURIs", kNoArg);

    registerFlag(ss, flag::convertUnsupportedImages, "convertUnsupportedImages", kNoArg);
    registerFlag(ss, flag::reportSkewedInverseBindMatrices, "reportSkewedInverseBindMatrices", kNoArg);
    registerFlag(ss, flag::clearOutputWindow, "clearOutputWindow", kNoArg);

    registerFlag(ss, flag::cameras, "cameras", true, kString);

    registerFlag(ss, flag::constantTranslationThreshold, "constantTranslationThreshold", kDouble);
    registerFlag(ss, flag::constantRotationThreshold, "constantRotationThreshold", kDouble);
    registerFlag(ss, flag::constantScalingThreshold, "constantScalingThreshold", kDouble);
    registerFlag(ss, flag::constantWeightsThreshold, "constantWeightsThreshold", kDouble);

    registerFlag(ss, flag::posPrecision, "posPrecision", kDouble);
    registerFlag(ss, flag::dirPrecision, "dirPrecision", kDouble);
    registerFlag(ss, flag::colPrecision, "colPrecision", kDouble);
    registerFlag(ss, flag::texPrecision, "texPrecision", kDouble);
    registerFlag(ss, flag::sclPrecision, "sclPrecision", kDouble);
    registerFlag(ss, flag::matPrecision, "matPrecision", kDouble);

    registerFlag(ss, flag::keepObjectNamespace, "keepMayaNamespaces", kNoArg);

    m_usage = ss.str();
}

SyntaxFactory::~SyntaxFactory() = default;

const SyntaxFactory &SyntaxFactory::get() {
    static SyntaxFactory syntax;
    return syntax;
}

MSyntax SyntaxFactory::createSyntax() {
    const MSyntax &s = get();
    return s;
}

void SyntaxFactory::registerFlag(std::stringstream &ss, const char *shortName, const char *longName, const MArgType argType1) {
    registerFlag(ss, shortName, longName, false, argType1);
}

void SyntaxFactory::registerFlag(std::stringstream &ss, const char *shortName, const char *longName, const bool isMultiUse, const MArgType argType1) {
    // short-name should be unique
    assert(m_argNames.find(shortName) == m_argNames.end());

    m_argNames[shortName] = longName;

    auto status = addFlag(shortName, longName, argType1);
    THROW_ON_FAILURE(status);

    if (isMultiUse) {
        makeFlagMultiUse(shortName);
    }

    const auto name1 = getArgTypeName(argType1);

    ss << "-" << std::setw(5) << std::left << shortName << longName;

    if (name1) {
        ss << ": " << name1;
    }

    if (isMultiUse) {
        ss << "+";
    }

    ss << endl;

    ss.flush();
}

class ArgChecker {
  public:
    ArgChecker(const MSyntax &syntax, const MArgList &argList, MStatus &status) : adb(syntax, argList, &status) {
        // TODO: How to provide more error information about what arguments are
        // wrong?
        throwOnFailure(status, "Invalid arguments");
    }

    void getObjects(MSelectionList &selection) const {
        throwOnFailure(adb.getObjects(selection), "failed to get selection");

        if (selection.length() < 1)
            throwOnFailure(MStatus::kInvalidParameter, "At least one object must be selected or passed to "
                                                       "the command");
    }

    MeshSemanticSet getSemanticSet(const char *shortName, const Semantic::SemanticKinds &defaultKinds) const {
        MeshSemanticSet semantics;

        // Always include position
        semantics.set(Semantic::POSITION, true);

        MString attrs;
        if (optional(shortName, attrs)) {
            MStringArray parts;
            const auto status = attrs.split('|', parts);
            throwOnArgument(status, shortName);
            for (auto i = 0U; i < parts.length(); ++i) {
                const auto kind = Semantic::parse(parts[i].asChar());
                semantics[kind] = true;
            }
        } else {
            for (auto kind : defaultKinds) {
                semantics[kind] = true;
            }
        }

        return semantics;
    }

    bool isFlagSet(const char *shortName) const {
        MStatus status;
        const auto result = adb.isFlagSet(shortName, &status);
        throwOnArgument(status, shortName);
        return result;
    }

    int flagUsageCount(const char *shortName) const { return adb.numberOfFlagUses(shortName); }

    template <typename T> void required(const char *shortName, T &value, const int flagIndex = 0, const int componentIndex = 0) const {
        MStatus status;

        if (!isFlagSet(shortName))
            throwInvalid(shortName, "Missing argument");

        if (flagUsageCount(shortName) == 1) {
            status = adb.getFlagArgument(shortName, componentIndex, value);
            throwOnArgument(status, shortName, "Failed to get required argument");
        } else {
            MArgList args;
            status = adb.getFlagArgumentList(shortName, flagIndex, args);
            throwOnArgument(status, shortName, formatted("Failed to get required multi-flag #%d argument", flagIndex).c_str());
            status = args.get(componentIndex, value);
            throwOnArgument(status, shortName, formatted("Failed to get required multi-flag #%d argument value", flagIndex).c_str());
        }
    }

    template <typename T> bool optional(const char *shortName, T &value, const int flagIndex = 0, const int componentIndex = 0) const {
        if (!adb.isFlagSet(shortName))
            return false;

        MStatus status;

        if (flagUsageCount(shortName) == 1) {
            status = adb.getFlagArgument(shortName, componentIndex, value);
            throwOnArgument(status, shortName, "Failed to get optional argument");
        } else {
            MArgList args;
            status = adb.getFlagArgumentList(shortName, flagIndex, args);
            throwOnArgument(status, shortName, formatted("Failed to get optional multi-flag #%d argument", flagIndex).c_str());
            status = args.get(componentIndex, value);
            throwOnArgument(status, shortName, formatted("Failed to get optional multi-flag #%d argument value", flagIndex).c_str());
        }

        return true;
    }

    bool optional(const char *shortName, float &value) const {
        double temp;
        if (!optional(shortName, temp))
            return false;
        value = static_cast<float>(temp);
        return true;
    }

    bool optional(const char *shortName, MSelectionList &list, int argIndex = 0) const {
        if (!adb.isFlagSet(shortName))
            return false;

        adb.getFlagArgument(shortName, argIndex, list);
        return true;
    }

    std::unique_ptr<IndentableStream> getOutputStream(const char *arg, const char *outputName, const fs::path &outputFolder,
                                                      std::ofstream &fileOutputStream) const {
        std::ostream *out = nullptr;

        if (adb.isFlagSet(arg)) {
            MString argPath;
            if (adb.getFlagArgument(arg, 0, argPath).error() || argPath.toLowerCase() == "console") {
                out = &cout;
            } else if (argPath.length() == 0 || argPath.substring(0, 0) == "-") {
                throwInvalid(arg, "requires an output filepath argument, or just "
                                  "'console' to print to Maya's console window");
            } else {
                const fs::path argumentPath(argPath.asChar());
                const fs::path absolutePath = argumentPath.is_relative() ? outputFolder / argumentPath : argumentPath;

                cout << prefix << "Writing " << outputName << " output to file " << absolutePath << endl;

                fileOutputStream.open(absolutePath);
                out = &fileOutputStream;
            }
        }

        return out ? std::make_unique<IndentableStream>(*out) : nullptr;
    }

    static void throwOnFailure(const MStatus &status, const char *message) {
        if (status.error()) {
            const auto statusStr = status.errorString().asChar();
            const auto usageStr = SyntaxFactory::get().usage();
            throw MayaException(status, formatted("%s (%s)\nUsage:\n%s", message, statusStr, usageStr));
        }
    }

    static void throwUsage(const char *message) {
        const auto usageStr = SyntaxFactory::get().usage();
        throw MayaException(MStatus::kFailure, formatted("%s\nUsage:\n%s", message, usageStr));
    }

    static void throwOnArgument(const MStatus &status, const char *shortArgName, const char *message = nullptr) {
        if (status.error()) {
            const auto longArgName = SyntaxFactory::get().longArgName(shortArgName);
            const auto statusStr = status.errorString().asChar();
            const auto usageStr = SyntaxFactory::get().usage();
            throw MayaException(status, message ? formatted("-%s (-%s): %s\nUsage:\n%s", shortArgName, longArgName, statusStr, usageStr)
                                                : formatted("-%s (-%s): %s %s\nUsage:\n%s", shortArgName, longArgName, message, statusStr, usageStr));
        }
    }

    static void throwInvalid(const char *shortArgName, const char *message = "Invalid parameter") {
        const auto longArgName = SyntaxFactory::get().longArgName(shortArgName);
        const auto usageStr = SyntaxFactory::get().usage();

        throw MayaException(MStatus::kInvalidParameter, formatted("%s -%s (%s)\nUsage:\n%s", message, shortArgName, longArgName, usageStr));
    }

  private:
    MArgDatabase adb;
};

Arguments::Arguments(const MArgList &args, const MSyntax &syntax) {
    // ReSharper disable CppExpressionWithoutSideEffects

    MStatus status;
    ArgChecker adb(syntax, args, status);

    MSelectionList userSelection;
    adb.getObjects(userSelection);

    selectedNodesOnly = adb.isFlagSet(flag::selectedNodesOnly);
    visibleNodesOnly = adb.isFlagSet(flag::visibleNodesOnly);

    MStringArray skippedObjects;

    for (uint selectionIndex = 0; selectionIndex < userSelection.length(); ++selectionIndex) {
        MDagPath dagPath;
        status = userSelection.getDagPath(selectionIndex, dagPath);

        if (status) {
            if (visibleNodesOnly && !dagPath.isVisible()) {
                skippedObjects.append(dagPath.partialPathName());
            } else {
                select(meshShapes, cameraShapes, dagPath, !selectedNodesOnly, !visibleNodesOnly);
            }
        } else {
            MayaException::printError(formatted("Failed to get DAG path of selected object #%d\n", selectionIndex));
        }
    }

    if (skippedObjects.length() > 0) {
        cout << prefix << "WARNING: -visibleNodesOnly will skip " << skippedObjects << endl;
    }

    adb.required(flag::outputFolder, outputFolder);
    adb.optional(flag::scaleFactor, globalScaleFactor);

    cleanOutputFolder = adb.isFlagSet(flag::cleanOutputFolder);

    glb = adb.isFlagSet(flag::binary);

    const fs::path outputFolderPath(outputFolder.asChar());
    m_mayaOutputStream = adb.getOutputStream(flag::dumpMaya, "Maya debug", outputFolderPath, m_mayaOutputFileStream);
    m_gltfOutputStream = adb.getOutputStream(flag::dumpGLTF, "glTF debug", outputFolderPath, m_gltfOutputFileStream);

    dumpMaya = m_mayaOutputStream.get();
    dumpGLTF = m_gltfOutputStream.get();
    dumpAccessorComponents = adb.isFlagSet(flag::dumpAccessorComponents);

    externalTextures = adb.isFlagSet(flag::externalTextures);
    splitMeshAnimation = adb.isFlagSet(flag::splitMeshAnimation);
    splitByReference = adb.isFlagSet(flag::splitByReference);
    separateAccessorBuffers = adb.isFlagSet(flag::separateAccessorBuffers);
    defaultMaterial = adb.isFlagSet(flag::defaultMaterial);
    colorizeMaterials = adb.isFlagSet(flag::colorizeMaterials);
    skipStandardMaterials = adb.isFlagSet(flag::skipStandardMaterials);
    skipMaterialTextures = adb.isFlagSet(flag::skipMaterialTextures);

    force32bitIndices = adb.isFlagSet(flag::force32bitIndices);
    disableNameAssignment = adb.isFlagSet(flag::disableNameAssignment);
    keepObjectNamespace = adb.isFlagSet(flag::keepObjectNamespace);
    skipSkinClusters = adb.isFlagSet(flag::skipSkinClusters);
    skipBlendShapes = adb.isFlagSet(flag::skipBlendShapes);
    redrawViewport = adb.isFlagSet(flag::redrawViewport);
    excludeUnusedTexcoord = adb.isFlagSet(flag::excludeUnusedTexcoord);
    ignoreSegmentScaleCompensation = adb.isFlagSet(flag::ignoreSegmentScaleCompensation);
    keepShapeNodes = adb.isFlagSet(flag::keepShapeNodes);
    bakeScalingFactor = adb.isFlagSet(flag::bakeScalingFactor);
    forceRootNode = adb.isFlagSet(flag::forceRootNode);
    forceAnimationChannels = adb.isFlagSet(flag::forceAnimationChannels);
    forceAnimationSampling = adb.isFlagSet(flag::forceAnimationSampling);
    hashBufferURIs = adb.isFlagSet(flag::hashBufferURIs);
    niceBufferURIs = adb.isFlagSet(flag::niceBufferURIs);
    convertUnsupportedImages = adb.isFlagSet(flag::convertUnsupportedImages);
    reportSkewedInverseBindMatrices = adb.isFlagSet(flag::reportSkewedInverseBindMatrices);
    clearOutputWindow = adb.isFlagSet(flag::clearOutputWindow);

    adb.optional(flag::globalOpacityFactor, opacityFactor);

    adb.optional(flag::constantTranslationThreshold, constantTranslationThreshold);
    adb.optional(flag::constantRotationThreshold, constantRotationThreshold);
    adb.optional(flag::constantScalingThreshold, constantScalingThreshold);
    adb.optional(flag::constantWeightsThreshold, constantWeightsThreshold);

    adb.optional(flag::posPrecision, posPrecision);
    adb.optional(flag::dirPrecision, dirPrecision);
    adb.optional(flag::colPrecision, colPrecision);
    adb.optional(flag::texPrecision, texPrecision);
    adb.optional(flag::sclPrecision, sclPrecision);
    adb.optional(flag::matPrecision, matPrecision);

    if (!adb.optional(flag::sceneName, sceneName)) {
        // Use filename without extension of current scene file.
        MFileIO fileIO;
        const auto currentFilePath = MFileIO::currentFile();

        MFileObject fileObj;
        fileObj.setRawFullName(currentFilePath);

        // Remove extension from filename. I really miss C#!
        std::string fileName(fileObj.resolvedName().asChar());

        const auto lastindex = fileName.find_last_of('.');
        sceneName = fileName.substr(0, lastindex).c_str();
    }

    mikkelsenTangentAngularThreshold = adb.isFlagSet(flag::mikkelsenTangentSpace) ? 180.0f : 0.0f;
    adb.optional(flag::mikkelsenTangentAngularThreshold, mikkelsenTangentAngularThreshold);

    debugTangentVectors = adb.isFlagSet(flag::debugTangentVectors);
    debugNormalVectors = adb.isFlagSet(flag::debugNormalVectors);

    adb.optional(flag::detectStepAnimations, detectStepAnimations);
    adb.optional(flag::debugVectorLength, debugVectorLength);
    adb.optional(flag::copyright, copyright);

    adb.optional(flag::gltfFileExtension, gltfFileExtension);
    adb.optional(flag::glbFileExtension, glbFileExtension);

    // Parse mesh deformers to ignore
    const auto deformerNameCount = adb.flagUsageCount(flag::ignoreMeshDeformers);
    for (auto deformerNameIndex = 0; deformerNameIndex < deformerNameCount; ++deformerNameIndex) {
        MString deformerName;
        adb.required(flag::ignoreMeshDeformers, deformerName, deformerNameIndex);
        ignoreMeshDeformers.add(deformerName);
    }

    // Parse mesh primitive attributes
    meshPrimitiveAttributes = adb.getSemanticSet(flag::meshPrimitiveAttributes, Semantic::kinds());
    blendPrimitiveAttributes = adb.getSemanticSet(flag::blendPrimitiveAttributes, Semantic::blendShapeKinds());

    // Parse animation clips
    const auto clipCount = adb.flagUsageCount(flag::animationClipName);
    animationClips.reserve(clipCount);

    initialValuesTime = clipCount > 0 ? MTime(0, MTime::kSeconds) : MAnimControl::currentTime();
    adb.optional(flag::initialValuesTime, initialValuesTime);

    const auto fpsCount = adb.flagUsageCount(flag::animationClipFrameRate);

    const auto stepDetectSampleCount = getStepDetectSampleCount();

    for (int clipIndex = 0; clipIndex < clipCount; ++clipIndex) {
        double fps;
        adb.required(flag::animationClipFrameRate, fps, fpsCount == 1 ? 0 : clipIndex);

        MString name;
        adb.required(flag::animationClipName, name, clipIndex);

        MTime start;
        adb.required(flag::animationClipStartTime, start, clipIndex);

        MTime end;
        adb.required(flag::animationClipEndTime, end, clipIndex);

        animationClips.emplace_back(name.asChar(), start, end, fps, stepDetectSampleCount);
    }

    // Sort clips by starting time.
    std::sort(animationClips.begin(), animationClips.end(),
              [](const AnimClipArg &left, const AnimClipArg &right) { return left.startTime < right.endTime; });

    // Print the animation clips
    for (const auto &clip : animationClips) {
        cout << prefix << "Exporting clip " << clip.name << ", start:" << clip.startTime << ", end: " << clip.endTime
             << ", duration:" << clip.duration() << ", frames: " << clip.frameCount() << ", rate: " << clip.framesPerSecond << "fps" << endl;
    }

    // Get extra cameras to export
    const auto extraCameraCount = adb.flagUsageCount(flag::cameras);

    for (auto flagIndex = 0; flagIndex < extraCameraCount; ++flagIndex) {
        MString cameraPattern;
        if (!adb.optional(flag::cameras, cameraPattern, flagIndex)) {
            continue;
        }

        MSelectionList cameraSelection;
        if (!cameraSelection.add(cameraPattern)) {
            cerr << prefix << "Skipping " << cameraPattern << ", it doesn't match any object" << endl;
            continue;
        }

        for (unsigned i = 0; i < cameraSelection.length(); ++i) {
            MDagPath dagPath;
            if (!cameraSelection.getDagPath(i, dagPath)) {
                cerr << prefix << "Skipping " << cameraPattern << " matched object #" << i << endl;
                continue;
            }

            if (!dagPath.hasFn(MFn::kTransform)) {
                cerr << prefix << "Skipping " << dagPath.partialPathName() << ", it is not a camera transform" << endl;
                continue;
            }

            unsigned shapeCount;
            status = dagPath.numberOfShapesDirectlyBelow(shapeCount);
            if (!status) {
                cerr << prefix << "Skipping " << dagPath.partialPathName() << ", it has no shapes attached to it" << endl;
                continue;
            }

            bool foundCameraShape = false;

            for (auto shapeIndex = 0U; shapeIndex < shapeCount; ++shapeIndex) {
                MDagPath shapePath = dagPath;
                status = shapePath.extendToShapeDirectlyBelow(shapeIndex);
                if (!status)
                    continue;

                MFnCamera camera(shapePath, &status);
                if (!status)
                    continue;

                cameraShapes.insert(shapePath);
                foundCameraShape = true;
            }

            if (!foundCameraShape) {
                cerr << prefix << "Skipping " << dagPath.partialPathName() << ", it has no cameras attached to it" << endl;
                continue;
            }
        }
    }

    // for (int i = 0; i < cameraCount; ++i)
    //{
    //    MObject camera;
    //    adb.required(flag::cameras, camera, i);
    //    cameras.add(camera);
    //}

    cout << prefix << "Exporting shapes:";
    for (auto &path : meshShapes) {
        cout << " " << path.partialPathName();
    }
    cout << endl;

    cout << prefix << "Exporting cameras:";
    for (auto &path : cameraShapes) {
        cout << " " << path.partialPathName();
    }
    cout << endl;

    cout << prefix << "Exporting to " << outputFolder << "/" << sceneName << "..." << endl;
}

Arguments::~Arguments() {
    if (m_mayaOutputFileStream.is_open()) {
        m_mayaOutputFileStream.flush();
        m_mayaOutputFileStream.close();
    }

    if (m_gltfOutputFileStream.is_open()) {
        m_gltfOutputFileStream.flush();
        m_gltfOutputFileStream.close();
    }
}

std::string Arguments::assignName(GLTF::Object &glObj, const MDagPath &dagPath, const MString &suffix) const {
    MStatus status;
    auto obj = dagPath.node(&status);
    THROW_ON_FAILURE(status)

    const MFnDependencyNode node(obj, &status);
    THROW_ON_FAILURE(status)

    return assignName(glObj, node, suffix);
}

std::string Arguments::assignName(GLTF::Object &glObj, const MFnDependencyNode &node, const MString &suffix) const {
    MStatus status;

    auto name = node.name(&status);
    THROW_ON_FAILURE(status)

    if (!keepObjectNamespace) {
        const auto ns = node.parentNamespace(&status);
        if (status && ns.length() > 0) {
            name.substitute(ns + ":", "");
        }
    }

    name += suffix;

    std::string result(name.asChar());

    if (!disableNameAssignment) {
        glObj.name = result;
    }

    return result;
}

void Arguments::select(Selection &shapeSelection, Selection &cameraSelection, const MDagPath &dagPath, const bool includeDescendants,
                       const bool includeInvisibleNodes) {
    MStatus status;

    std::string debugName{dagPath.partialPathName().asChar()};

    if (includeInvisibleNodes || dagPath.isVisible()) {
        if (dagPath.hasFn(MFn::kTransform)) {
            unsigned shapeCount;
            status = dagPath.numberOfShapesDirectlyBelow(shapeCount);

            if (status) {
                for (auto shapeIndex = 0U; shapeIndex < shapeCount; ++shapeIndex) {
                    MDagPath shapePath = dagPath;
                    status = shapePath.extendToShapeDirectlyBelow(shapeIndex);
                    if (status) {
                        MFnMesh mesh(shapePath, &status);
                        // Do not include intermediate meshes
                        if (status && !mesh.isIntermediateObject()) {
                            shapeSelection.insert(shapePath);
                        }

                        MFnCamera camera(shapePath, &status);
                        // Do not include intermediate cameras
                        if (status && !camera.isIntermediateObject()) {
                            cameraSelection.insert(shapePath);
                        }
                    }
                }
            }
        } else if (dagPath.hasFn(MFn::kMesh)) {
            MFnMesh mesh(dagPath, &status);
            // Do not include intermediate meshes
            if (status && !mesh.isIntermediateObject()) {
                MDagPath shapePath;
                status = mesh.getPath(shapePath);
                if (status) {
                    shapeSelection.insert(shapePath);
                } else {
                    cerr << prefix << "Failed to get DAG path of " << mesh.partialPathName() << endl;
                }
            }
        } else if (dagPath.hasFn(MFn::kCamera)) {
            MFnCamera camera(dagPath, &status);
            // Do not include intermediate cameras
            if (status && !camera.isIntermediateObject()) {
                MDagPath cameraPath;
                status = camera.getPath(cameraPath);
                if (status) {
                    cameraSelection.insert(cameraPath);
                } else {
                    cerr << prefix << "Failed to get DAG path of " << camera.partialPathName() << endl;
                }
            }
        }

        if (includeDescendants) {
            const auto childCount = dagPath.childCount(&status);
            THROW_ON_FAILURE(status);

            for (auto childIndex = 0U; childIndex < childCount; ++childIndex) {
                const auto child = dagPath.child(childIndex, &status);
                MDagPath childDagPath = dagPath;
                status = childDagPath.push(child);
                THROW_ON_FAILURE(status);
                select(shapeSelection, cameraSelection, childDagPath, includeDescendants, includeInvisibleNodes);
            }
        }
    }
}

MTime AnimClipArg::duration() const { return MTime(frameCount() * (1.0 / framesPerSecond), MTime::kSeconds); }

int AnimClipArg::frameCount() const {
    const auto exactStartFrame = startTime.as(MTime::kSeconds) * framesPerSecond;
    const auto exactEndFrame = endTime.as(MTime::kSeconds) * framesPerSecond;
    const auto startFrame = round(exactStartFrame);
    const auto endFrame = round(exactEndFrame);
    const auto count = static_cast<int>(endFrame - startFrame) + 1;
    return count;
}
