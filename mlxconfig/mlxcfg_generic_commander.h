/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * mlxcfg_generic_commander.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_GENERIC_COMMANDER_H_
#define MLXCFG_GENERIC_COMMANDER_H_

#include <errmsg.h>
#include <tools_layouts/tools_open_layouts.h>
#include "mlxcfg_commander.h"
#include "mlxcfg_db_manager.h"

class GenericCommander : public Commander {
private:
    mfile* _mf;
    MlxcfgDBManager *_dbManager;

    void supportsNVData();
    void printEnums(ParamView p, string& s);
    bool checkDependency(TLVConf* cTLV, string dStr);
    void filterByDependency(TLVConf* cTLV, const vector<pair<ParamView, string> >& dependencyTable, vector<ParamView>& result);
    void queryTLV(TLVConf* conf, std::vector<ParamView>& paramsConf, QueryType qt);
    void getAllConfigurations(std::vector<TLVConfView>& confs);
    void excludeDuplicatedTLVs(vector<TLVConfView>& s, vector<TLVConfView>& d);
    void printTLVConfViews(FILE* f, vector<TLVConfView>& v);
    void printParamViews(FILE* f, vector<ParamView>& v);
    void genXMLTemplateAux(vector<string> tlvs, string& xmlTemplate,
            bool allAttrs, bool withVal, bool defaultAttrVal);
public:
    GenericCommander(mfile* mf, string dbName);
    ~GenericCommander();
    void printLongDesc(FILE*);
    void queryParamViews(std::vector<ParamView>& paramsToQuery, QueryType qt = QueryNext);
    void queryAll(std::vector<ParamView>& params, QueryType qt = QueryNext);
    void getCfg(ParamView& cfgParam, QueryType qt = QueryNext);
    void setCfg(std::vector<ParamView>& params, bool force);
    bool isDefaultSupported();
    void clearSemaphore();
    void invalidateCfgs();
    const char* loadConfigurationGetStr();
    void setRawCfg(std::vector<u_int32_t> rawTlvVec);
    void dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump);
    void backupCfgs(std::vector<std::pair<u_int32_t, std::vector<u_int8_t> > >& cfgs);
    void updateParamViewValue(ParamView&, std::string);

    void genTLVsList(vector<string>& tlvs);
    void genXMLTemplate(vector<string> tlvs, string& xml, bool allAttrs);
    void XML2TLVConf(const string xmlContent, vector<TLVConf*>& tlvs);
    void binTLV2XML(vector<u_int32_t>binTLV, string& xml);
    void raw2XML(const vector<string> lines, string& xml);
    void XML2Raw(const string xml, string& raw);
};

class RawCfgParams5thGen : public ErrMsg
{
public:
    RawCfgParams5thGen();
    ~RawCfgParams5thGen() {}
    int setRawData(const std::vector<u_int32_t>& tlvBuff);
    int setOnDev(mfile* mf);
    std::string dumpTlv();
private:
    int verifyTlv();
    std::vector<u_int32_t> _tlvBuff;
    struct tools_open_nvda _nvdaTlv;
};

#endif /* MLXCFG_GENERIC_COMMANDER_H_ */
