#include "pika_admin.h"
#include "pika_kv.h"
#include "pika_hash.h"

static std::unordered_map<std::string, CmdInfo*> cmd_infos(300);    /* Table for CmdInfo */

//Remember the first arg is the command name
void InitCmdInfoTable() {
  //Admin
  ////Slaveof
  CmdInfo* slaveofptr = new CmdInfo(kCmdNameSlaveof, -3, kCmdFlagsRead | kCmdFlagsAdmin);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameSlaveof, slaveofptr));
  ////Trysync
  CmdInfo* trysyncptr = new CmdInfo(kCmdNameTrysync, 5, kCmdFlagsRead | kCmdFlagsAdmin);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameTrysync, trysyncptr));

  //Kv
  ////SetCmd
  CmdInfo* setptr = new CmdInfo(kCmdNameSet, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameSet, setptr));
  ////GetCmd
  CmdInfo* getptr = new CmdInfo(kCmdNameGet, 2, kCmdFlagsRead | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameGet, getptr));
  ////DelCmd
  CmdInfo* delptr = new CmdInfo(kCmdNameDel, -2, kCmdFlagsWrite | kCmdFlagsKv); //whethre it should be kCmdFlagsKv
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameDel, delptr));
  ////IncrCmd
  CmdInfo* incrptr = new CmdInfo(kCmdNameIncr, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameIncr, incrptr));
  ////IncrbyCmd
  CmdInfo* incrbyptr = new CmdInfo(kCmdNameIncrby, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameIncrby, incrbyptr));
  ////IncrbyfloatCmd
  CmdInfo* incrbyfloatptr = new CmdInfo(kCmdNameIncrbyfloat, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameIncrbyfloat, incrbyfloatptr));
  ////Decr
  CmdInfo* decrptr = new CmdInfo(kCmdNameDecr, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameDecr, decrptr));
  ////Decrby
  CmdInfo* decrbyptr = new CmdInfo(kCmdNameDecrby, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameDecrby, decrbyptr));
  ////Getset
  CmdInfo* getsetptr = new CmdInfo(kCmdNameGetset, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameGetset, getsetptr));
  ////Append
  CmdInfo* appendptr = new CmdInfo(kCmdNameAppend, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameAppend, appendptr));
  ////Mget
  CmdInfo* mgetptr = new CmdInfo(kCmdNameMget, -2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameMget, mgetptr));
  ////Keys
  CmdInfo* keysptr = new CmdInfo(kCmdNameKeys, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameKeys, keysptr));
  ////Setnx
  CmdInfo* setnxptr = new CmdInfo(kCmdNameSetnx, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameSetnx, setnxptr));
  ////Setex
  CmdInfo* setexptr = new CmdInfo(kCmdNameSetex, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameSetex, setexptr));
  ////MSet
  CmdInfo* msetptr = new CmdInfo(kCmdNameMset, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameMset, msetptr));
  ////MSetnx
  CmdInfo* msetnxptr = new CmdInfo(kCmdNameMsetnx, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameMsetnx, msetnxptr));
  ////Getrange
  CmdInfo* getrangeptr = new CmdInfo(kCmdNameGetrange, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameGetrange, getrangeptr));
  ////Setrange
  CmdInfo* setrangeptr = new CmdInfo(kCmdNameSetrange, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameSetrange, setrangeptr));
  ////Strlen
  CmdInfo* strlenptr = new CmdInfo(kCmdNameStrlen, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameStrlen, strlenptr));
  ////Exists
  CmdInfo* existsptr = new CmdInfo(kCmdNameExists, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameExists, existsptr));
  ////Expire
  CmdInfo* expireptr = new CmdInfo(kCmdNameExpire, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameExpire, expireptr));
  ////Pexpire
  CmdInfo* pexpireptr = new CmdInfo(kCmdNamePexpire, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNamePexpire, pexpireptr));
  ////Expireat
  CmdInfo* expireatptr = new CmdInfo(kCmdNameExpireat, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameExpireat, expireatptr));
  ////Pexpireat
  CmdInfo* pexpireatptr = new CmdInfo(kCmdNamePexpireat, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNamePexpireat, pexpireatptr));
  ////Ttl
  CmdInfo* ttlptr = new CmdInfo(kCmdNameTtl, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameTtl, ttlptr));
  ////Pttl
  CmdInfo* pttlptr = new CmdInfo(kCmdNameTtl, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNamePttl, pttlptr));
  ////Persist
  CmdInfo* persistptr = new CmdInfo(kCmdNamePersist, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNamePersist, persistptr));
  ////Persist
  CmdInfo* typeptr = new CmdInfo(kCmdNameType, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameType, typeptr));
  ////Scan
  CmdInfo* scanptr = new CmdInfo(kCmdNameScan, -2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameScan, scanptr));
  //Hash
  ////HDel
  CmdInfo* hdelptr = new CmdInfo(kCmdNameHDel, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHDel, hdelptr));
  ////HSet
  CmdInfo* hsetptr = new CmdInfo(kCmdNameHSet, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHSet, hsetptr));
  ////HGet
  CmdInfo* hgetptr = new CmdInfo(kCmdNameHGet, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHGet, hgetptr));
  ////HGetall
  CmdInfo* hgetallptr = new CmdInfo(kCmdNameHGetall, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHGetall, hgetallptr));
  ////HExists
  CmdInfo* hexistsptr = new CmdInfo(kCmdNameHExists, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHExists, hexistsptr));
  ////HIncrby
  CmdInfo* hincrbyptr = new CmdInfo(kCmdNameHIncrby, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHIncrby, hincrbyptr));
  ////HIncrbyfloat
  CmdInfo* hincrbyfloatptr = new CmdInfo(kCmdNameHIncrbyfloat, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHIncrbyfloat, hincrbyfloatptr));
  ////HKeys
  CmdInfo* hkeysptr = new CmdInfo(kCmdNameHKeys, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHKeys, hkeysptr));
  ///HLen
  CmdInfo* hlenptr = new CmdInfo(kCmdNameHLen, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHLen, hlenptr));
  ///HMget
  CmdInfo* hmgetptr = new CmdInfo(kCmdNameHMget, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHMget, hmgetptr));
  ///HMset
  CmdInfo* hmsetptr = new CmdInfo(kCmdNameHMset, -4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHMset, hmsetptr));
  ///HMset
  CmdInfo* hsetnxptr = new CmdInfo(kCmdNameHSetnx, 4, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHSetnx, hsetnxptr));
  ///HStrlen
  CmdInfo* hstrlenptr = new CmdInfo(kCmdNameHStrlen, 3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHStrlen, hstrlenptr));
  ///HVals
  CmdInfo* hvalsptr = new CmdInfo(kCmdNameHVals, 2, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHVals, hvalsptr));
  ///HScan
  CmdInfo* hscanptr = new CmdInfo(kCmdNameHScan, -3, kCmdFlagsWrite | kCmdFlagsKv);
  cmd_infos.insert(std::pair<std::string, CmdInfo*>(kCmdNameHScan, hscanptr));

  //List

  //Zset

  //Set
}

void DestoryCmdInfoTable() {
  std::unordered_map<std::string, CmdInfo*>::const_iterator it = cmd_infos.begin();
  for (; it != cmd_infos.end(); ++it) {
    delete it->second;
  }
}

const CmdInfo* GetCmdInfo(const std::string& opt) {
  std::unordered_map<std::string, CmdInfo*>::const_iterator it = cmd_infos.find(opt);
  if (it != cmd_infos.end()) {
    return it->second;
  }
  return NULL;
}

void InitCmdTable(std::unordered_map<std::string, Cmd*> *cmd_table) {
  //Admin
  ////Slaveof
  Cmd* slaveofptr = new SlaveofCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameSlaveof, slaveofptr));
  ////Trysync
  Cmd* trysyncptr = new TrysyncCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameTrysync, trysyncptr));

  //Kv
  ////SetCmd
  Cmd* setptr = new SetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameSet, setptr));
  ////GetCmd
  Cmd* getptr = new GetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameGet, getptr));
  ////DelCmd
  Cmd* delptr = new DelCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameDel, delptr));
  ////IncrCmd
  Cmd* incrptr = new IncrCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameIncr, incrptr));
  ////IncrbyCmd
  Cmd* incrbyptr = new IncrbyCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameIncrby, incrbyptr));
  ////IncrbyfloatCmd
  Cmd* incrbyfloatptr = new IncrbyfloatCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameIncrbyfloat, incrbyfloatptr));
  ////DecrCmd
  Cmd* decrptr = new DecrCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameDecr, decrptr));
  ////DecrbyCmd
  Cmd* decrbyptr = new DecrbyCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameDecrby, decrbyptr));
  ////GetsetCmd
  Cmd* getsetptr = new GetsetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameGetset, getsetptr));
  ////AppendCmd
  Cmd* appendptr = new AppendCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameAppend, appendptr));
  ////MgetCmd
  Cmd* mgetptr = new MgetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameMget, mgetptr));
  ////KeysCmd
  Cmd* keysptr = new KeysCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameKeys, keysptr));
  ////SetnxCmd
  Cmd* setnxptr = new SetnxCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameSetnx, setnxptr));
  ////SetexCmd
  Cmd* setexptr = new SetexCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameSetex, setexptr));
  ////MSetCmd
  Cmd* msetptr = new MsetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameMset, msetptr));
  ////MSetCmd
  Cmd* msetnxptr = new MsetnxCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameMsetnx, msetnxptr));
  ////GetrangeCmd
  Cmd* getrangeptr = new GetrangeCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameGetrange, getrangeptr));
  ////SetrangeCmd
  Cmd* setrangeptr = new SetrangeCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameSetrange, setrangeptr));
  ////StrlenCmd
  Cmd* strlenptr = new StrlenCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameStrlen, strlenptr));
  ////ExistsCmd
  Cmd* existsptr = new ExistsCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameExists, existsptr));
  ////ExpireCmd
  Cmd* expireptr = new ExpireCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameExpire, expireptr));
  ////PexpireCmd
  Cmd* pexpireptr = new PexpireCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNamePexpire, pexpireptr));
  ////ExpireatCmd
  Cmd* expireatptr = new ExpireatCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameExpireat, expireatptr));
  ////PexpireatCmd
  Cmd* pexpireatptr = new PexpireatCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNamePexpireat, pexpireatptr));
  ////TtlCmd
  Cmd* ttlptr = new TtlCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameTtl, ttlptr));
  ////PttlCmd
  Cmd* pttlptr = new PttlCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNamePttl, pttlptr));
  ////PersistCmd
  Cmd* persistptr = new PersistCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNamePersist, persistptr));
  ////TypeCmd
  Cmd* typeptr = new TypeCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameType, typeptr));
  ////ScanCmd
  Cmd* scanptr = new ScanCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameScan, scanptr));
  //Hash
  ////HDelCmd
  Cmd* hdelptr = new HDelCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHDel, hdelptr));  
  ////HSetCmd
  Cmd* hsetptr = new HSetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHSet, hsetptr));  
  ////HGetCmd
  Cmd* hgetptr = new HGetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHGet, hgetptr));  
  ////HGetallCmd
  Cmd* hgetallptr = new HGetallCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHGetall, hgetallptr));  
  ////HExistsCmd
  Cmd* hexistsptr = new HExistsCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHExists, hexistsptr));  
  ////HIncrbyCmd
  Cmd* hincrbyptr = new HIncrbyCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHIncrby, hincrbyptr));  
  ////HIncrbyfloatCmd
  Cmd* hincrbyfloatptr = new HIncrbyfloatCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHIncrbyfloat, hincrbyfloatptr));  
  ////HKeysCmd
  Cmd* hkeysptr = new HKeysCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHKeys, hkeysptr));  
  ////HLenCmd
  Cmd* hlenptr = new HLenCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHLen, hlenptr));  
  ////HMgetCmd
  Cmd* hmgetptr = new HMgetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHMget, hmgetptr));  
  ////HMsetCmd
  Cmd* hmsetptr = new HMsetCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHMset, hmsetptr));  
  ////HSetnxCmd
  Cmd* hsetnxptr = new HSetnxCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHSetnx, hsetnxptr));  
  ////HStrlenCmd
  Cmd* hstrlenptr = new HStrlenCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHStrlen, hstrlenptr));  
  ////HValsCmd
  Cmd* hvalsptr = new HValsCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHVals, hvalsptr));  
  ////HScanCmd
  Cmd* hscanptr = new HScanCmd();
  cmd_table->insert(std::pair<std::string, Cmd*>(kCmdNameHScan, hscanptr));  
  //List

  //Zset

  //Set

}

Cmd* GetCmdFromTable(const std::string& opt, 
    const std::unordered_map<std::string, Cmd*> &cmd_table) {
  std::unordered_map<std::string, Cmd*>::const_iterator it = cmd_table.find(opt);
  if (it != cmd_table.end()) {
    return it->second;
  }
  return NULL;
}

void DestoryCmdTable(std::unordered_map<std::string, Cmd*> &cmd_table) {
  std::unordered_map<std::string, Cmd*>::const_iterator it = cmd_table.begin();
  for (; it != cmd_table.end(); ++it) {
    delete it->second;
  }
}
