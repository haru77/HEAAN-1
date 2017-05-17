#include "EvaluatorUtils.h"

CZZ EvaluatorUtils::evaluateVal(const double& xr, const double& xi, const long& logp) {
	if(logp < 31) {
		long p = 1 << logp;
		ZZ pxexpr = to_ZZ(xr * p);
		ZZ pxexpi = to_ZZ(xi * p);
		return CZZ(pxexpr, pxexpi);
	} else {
		long tmp = (1 << 30);
		ZZ pxexpr = to_ZZ(xr * tmp) << (logp - 30);
		ZZ pxexpi = to_ZZ(xi * tmp) << (logp - 30);
		return CZZ(pxexpr, pxexpi);
	}
}

CZZ EvaluatorUtils::evaluateRandomVal(const long& logp) {
	double mr = (double)rand() / RAND_MAX;
	double mi = (double)rand() / RAND_MAX;
	return evaluateVal(mr, mi, logp);
}

vector<CZZ> EvaluatorUtils::evaluateRandomVals(const long& size, const long& logp) {
	vector<CZZ> res;
	for (long i = 0; i < size; ++i) {
		double mr = (double)rand() / RAND_MAX;
		double mi = (double)rand() / RAND_MAX;
		CZZ m = EvaluatorUtils::evaluateVal(mr, mi, logp);
		res.push_back(m);
	}
	return res;
}

CZZ EvaluatorUtils::evaluatePow(const double& xr, const double& xi, const long& degree, const long& logp) {
	CZZ m = evaluateVal(xr, xi, logp);
	CZZ res = m;
	for (int i = 0; i < degree; ++i) {
		res = (res * m) >> logp;
	}
	return res;
}

CZZ EvaluatorUtils::evaluatePow2(const double& xr, const double& xi, const long& logDegree, const long& logp) {
	CZZ res = evaluateVal(xr, xi, logp);
	for (int i = 0; i < logDegree; ++i) {
		res = (res * res) >> logp;
	}
	return res;
}

vector<CZZ> EvaluatorUtils::evaluatePowvec(const double& xr, const double& xi, const long& degree, const long& logp) {
	vector<CZZ> res;
	CZZ m = evaluateVal(xr, xi, logp);
	res.push_back(m);
	for (int i = 0; i < degree - 1; ++i) {
		CZZ pow = (res[i] * m) >> logp;
		res.push_back(pow);
	}
	return res;
}

vector<CZZ> EvaluatorUtils::evaluatePow2vec(const double& xr, const double& xi, const long& logDegree, const long& logp) {
	vector<CZZ> res;
	CZZ m = evaluateVal(xr, xi, logp);
	res.push_back(m);
	for (int i = 0; i < logDegree; ++i) {
		CZZ pow2 = (res[i] * res[i]) >> logp;
		res.push_back(pow2);
	}
	return res;
}

CZZ EvaluatorUtils::evaluateInverse(const double& xr, const double& xi, const long& logp) {
	double xinvr = xr / (xr * xr + xi * xi);
	double xinvi = -xi / (xr * xr + xi * xi);

	return evaluateVal(xinvr, xinvi, logp);
}

CZZ EvaluatorUtils::evaluateExponent(const double& xr, const double& xi, const long& logp) {
	double xrexp = exp(xr);
	double xexpr = xrexp * cos(xi);
	double xexpi = xrexp * sin(xi);

	return evaluateVal(xexpr, xexpi, logp);
}

CZZ EvaluatorUtils::evaluateSigmoid(const double& xr, const double& xi, const long& logp) {
	double xrexp = exp(xr);
	double xexpr = xrexp * cos(xi);
	double xexpi = xrexp * sin(xi);

	double xsigmoidr = (xexpr * (xexpr + 1) + (xexpi * xexpi)) / ((xexpr + 1) * (xexpr + 1) + (xexpi * xexpi));
	double xsigmoidi = xexpi / ((xexpr + 1) * (xexpr + 1) + (xexpi * xexpi));

	return evaluateVal(xsigmoidr, xsigmoidi, logp);
}
