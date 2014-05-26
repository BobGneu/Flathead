(function () {

	// Namespace UMath
	assert(typeof UMath === "object", "UMath is supposed to be defined as an object");

	// constants
	assert(typeof UMath.PI === "number", "PI is a number");
	assert(UMath.PI === 3.1415927410125732, "PI is supposed to be 3.1415927410125732 - " + UMath.PI);

	assert(typeof UMath.SMALL_NUMBER === "number", "SMALL_NUMBER is a number");
	assert(UMath.SMALL_NUMBER === 9.99999993922529e-9, "SMALL_NUMBER is supposed to be 9.99999993922529e-9 - " + UMath.SMALL_NUMBER);

	assert(typeof UMath.KINDA_SMALL_NUMBER === "number", "KINDA_SMALL_NUMBER is a number");
	assert(UMath.KINDA_SMALL_NUMBER === 0.00009999999747378752, "KINDA_SMALL_NUMBER is supposed to be 0.00009999999747378752 - " + UMath.KINDA_SMALL_NUMBER);

	assert(typeof UMath.BIG_NUMBER === "number", "BIG_NUMBER is a number");
	assert(UMath.BIG_NUMBER === 3.3999999521443642e+38, "BIG_NUMBER is supposed to be 3.3999999521443642e+38 - " + UMath.BIG_NUMBER);

	assert(typeof UMath.EULERS_NUMBER === "number", "EULERS_NUMBER is a number");
	assert(UMath.EULERS_NUMBER === 2.7182817459106445, "EULERS_NUMBER is supposed to be 2.7182817459106445 - " + UMath.EULERS_NUMBER);

	assert(typeof UMath.MAX_FLT === "number", "MAX_FLT is a number");
	assert(UMath.MAX_FLT === 3.4028234663852886e+38, "MAX_FLT is supposed to be 3.4028234663852886e+38 - " + UMath.MAX_FLT);

	assert(typeof UMath.INV_PI === "number", "INV_PI is a number");
	assert(UMath.INV_PI === 0.31830987334251404, "INV_PI is supposed to be 0.31830987334251404 - " + UMath.INV_PI);

	assert(typeof UMath.HALF_PI === "number", "HALF_PI is a number");
	assert(UMath.HALF_PI === 1.5707963705062866, "HALF_PI is supposed to be 1.5707963705062866 - " + UMath.HALF_PI);

	assert(typeof UMath.DELTA === "number", "DELTA is a number");
	assert(UMath.DELTA === 0.000009999999747378752, "DELTA is supposed to be 0.000009999999747378752 - " + UMath.DELTA);

	assert(typeof UMath.FLOAT_NORMAL_THRESH === "number", "FLOAT_NORMAL_THRESH is a number");
	assert(UMath.FLOAT_NORMAL_THRESH === 0.00009999999747378752, "FLOAT_NORMAL_THRESH is supposed to be 0.00009999999747378752 - " + UMath.FLOAT_NORMAL_THRESH);

	assert(typeof UMath.THRESH_POINT_ON_PLANE === "number", "THRESH_POINT_ON_PLANE is a number");
	assert(UMath.THRESH_POINT_ON_PLANE === 0.10000000149011612, "THRESH_POINT_ON_PLANE is supposed to be 0.10000000149011612 - " + UMath.THRESH_POINT_ON_PLANE);

	assert(typeof UMath.THRESH_POINT_ON_SIDE === "number", "THRESH_POINT_ON_SIDE is a number");
	assert(UMath.THRESH_POINT_ON_SIDE === 0.20000000298023224, "THRESH_POINT_ON_SIDE is supposed to be 0.20000000298023224 - " + UMath.THRESH_POINT_ON_SIDE);

	assert(typeof UMath.THRESH_POINTS_ARE_SAME === "number", "THRESH_POINTS_ARE_SAME is a number");
	assert(UMath.THRESH_POINTS_ARE_SAME === 0.000019999999494757503, "THRESH_POINTS_ARE_SAME is supposed to be 0.000019999999494757503 - " + UMath.THRESH_POINTS_ARE_SAME);

	assert(typeof UMath.THRESH_POINTS_ARE_NEAR === "number", "THRESH_POINTS_ARE_NEAR is a number");
	assert(UMath.THRESH_POINTS_ARE_NEAR === 0.014999999664723873, "THRESH_POINTS_ARE_NEAR is supposed to be 0.014999999664723873 - " + UMath.THRESH_POINTS_ARE_NEAR);

	assert(typeof UMath.THRESH_NORMALS_ARE_SAME === "number", "THRESH_NORMALS_ARE_SAME is a number");
	assert(UMath.THRESH_NORMALS_ARE_SAME === 0.000019999999494757503, "THRESH_NORMALS_ARE_SAME is supposed to be 0.000019999999494757503 - " + UMath.THRESH_NORMALS_ARE_SAME);

	assert(typeof UMath.THRESH_VECTORS_ARE_NEAR === "number", "THRESH_VECTORS_ARE_NEAR is a number");
	assert(UMath.THRESH_VECTORS_ARE_NEAR === 0.00039999998989515007, "THRESH_VECTORS_ARE_NEAR is supposed to be 0.00039999998989515007 - " + UMath.THRESH_VECTORS_ARE_NEAR);

	assert(typeof UMath.THRESH_SPLIT_POLY_WITH_PLANE === "number", "THRESH_SPLIT_POLY_WITH_PLANE is a number");
	assert(UMath.THRESH_SPLIT_POLY_WITH_PLANE === 0.25, "THRESH_SPLIT_POLY_WITH_PLANE is supposed to be 0.25 - " + UMath.THRESH_SPLIT_POLY_WITH_PLANE);

	assert(typeof UMath.THRESH_SPLIT_POLY_PRECISELY === "number", "THRESH_SPLIT_POLY_PRECISELY is a number");
	assert(UMath.THRESH_SPLIT_POLY_PRECISELY === 0.009999999776482582, "THRESH_SPLIT_POLY_PRECISELY is supposed to be 0.009999999776482582 - " + UMath.THRESH_SPLIT_POLY_PRECISELY);

	assert(typeof UMath.THRESH_ZERO_NORM_SQUARED === "number", "THRESH_ZERO_NORM_SQUARED is a number");
	assert(UMath.THRESH_ZERO_NORM_SQUARED === 0.00009999999747378752, "THRESH_ZERO_NORM_SQUARED is supposed to be 0.00009999999747378752 - " + UMath.THRESH_ZERO_NORM_SQUARED);

	assert(typeof UMath.THRESH_VECTORS_ARE_PARALLEL === "number", "THRESH_VECTORS_ARE_PARALLEL is a number");
	assert(UMath.THRESH_VECTORS_ARE_PARALLEL === 0.019999999552965164, "THRESH_VECTORS_ARE_PARALLEL is supposed to be 0.019999999552965164 - " + UMath.THRESH_VECTORS_ARE_PARALLEL);

	// abs
	assert(typeof UMath.abs === "function", "abs is supposed to be defined as a function");
	assert(UMath.abs(42) === 42, "abs is supposed to return a positive value");
	assert(UMath.abs(-42) === 42, "abs is supposed to return a positive value");

	// acos
	assert(typeof UMath.acos === "function", "acos is supposed to be defined as a function");
	assert(UMath.acos(0.5) === 1.0471975803375244, "acos is supposed to return 1.0471975803375244");
	assert(UMath.acos(0.5) * 180 / UMath.PI === 60, "acos is supposed to be 60");

	// radiansToDegrees
	assert(typeof UMath.radiansToDegrees === "function", "radiansToDegrees is supposed to be defined as a function");
	assert(UMath.radiansToDegrees(UMath.acos(0.5)) === 60, "radiansToDegrees is supposed to be 60");

	// degreesToRadians
	assert(typeof UMath.degreesToRadians === "function", "degreesToRadians is supposed to be defined as a function");
	assert(UMath.degreesToRadians(60) === UMath.acos(0.5), "degreesToRadians is supposed to be 1.0471975803375244");

	// unwindRadians
	assert(typeof UMath.unwindRadians === "function", "unwindRadians is supposed to be defined as a function");
	assert(UMath.unwindRadians(60) === -2.831851005554199, "unwindRadians is supposed to be 2.831851005554199");

    // unwindDegrees
	assert(typeof UMath.unwindDegrees === "function", "unwindDegrees is supposed to be defined as a function");
	assert(UMath.unwindDegrees(600) === -120, "unwindDegrees is supposed to be -120");

    // asin
	assert(typeof UMath.asin === "function", "asin is supposed to be defined as a function");
	assert(UMath.asin(0.5) === 0.5235987901687622, "asin is supposed to be 0.5235987901687622");

    // atan
	assert(typeof UMath.atan === "function", "atan is supposed to be defined as a function");
	assert(UMath.atan(0.5) === 0.46364760398864746, "atan is supposed to be 0.46364760398864746");

    // atan2
	assert(typeof UMath.atan2 === "function", "atan2 is supposed to be defined as a function");
	assert(UMath.atan2(0.5, 0.5) === 0.7853981852531433, "atan2 is supposed to be 0.7853981852531433");

    // ceil
	assert(typeof UMath.ceil === "function", "ceil is supposed to be defined as a function");
	assert(UMath.ceil(44.20) === 45, "ceil is supposed to return 45");
	assert(UMath.ceil(-44.20) === -44, "ceil is supposed to return -44 | " + UMath.ceil(-44.20));

	// clamp
	assert(typeof UMath.clamp === "function", "acos is supposed to be defined as a function");
	assert(UMath.clamp(0.5, 0, 1) === 0.5, "acos is supposed to return 0.5");
	assert(UMath.clamp(-0.5, 0, 1) === 0, "acos is supposed to return 0");
	assert(UMath.clamp(1.5, 0, 1) === 1, "acos is supposed to return 1");

    // clampAngle
	assert(typeof UMath.clampAngle === "function", "clampAngle is supposed to be defined as a function");
	assert(UMath.clampAngle(15, 0, 1) === 1, "clampAngle is supposed to return 1");
	assert(UMath.clampAngle(-15, 0, 1) === 0, "clampAngle is supposed to return 1");
	assert(UMath.clampAngle(15, 0, 30) === 15, "clampAngle is supposed to return 15 | " + UMath.clampAngle(15, 0, 30));

    // cos
	assert(typeof UMath.cos === "function", "cos is supposed to be defined as a function");
	assert(UMath.cos(0.5) === 0.8775825500488281, "cos is supposed to be 0.8775825500488281 | " + UMath.cos(0.5));

    // exp
	assert(typeof UMath.exp === "function", "exp is supposed to be defined as a function");
	assert(UMath.exp(5) === 148.4131622314453, "exp is supposed to be 148.4131622314453 | " + UMath.exp(5));

    // findDeltaAngle
	assert(typeof UMath.findDeltaAngle === "function", "findDeltaAngle is supposed to be defined as a function");
	assert(UMath.findDeltaAngle(15, 30) === 8.716814041137695, "findDeltaAngle is supposed to be 8.716814041137695 | " + UMath.findDeltaAngle(15, 30));

})();