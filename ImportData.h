#ifndef IMPORTDATA_H
#define IMPORTDATA_H

#include <map>
#include <Qobject>

struct ParamsBase;

struct SDR2HDR {
    int val1;
};

struct Sharnping {
    int val2;
};

struct ParamsBase {
    virtual ~ParamsBase() {}

    //1
    const SDR2HDR* getSDR2HDR() const {
        return dynamic_cast<const SDR2HDR*>(this);
    }

    const Sharnping* getSharnping() const {
        return dynamic_cast<const Sharnping*>(this);
    }
};

struct ImportData {
    quint64 tid;
    QString path;
    QString name;
    QString SrcReso;
    QString outReso;
    QString format;

    //1 浅拷贝
    ParamsBase* param1;

    //2
    SDR2HDR sdr2hdr;
    Sharnping sharnping;

    //3
    int val1;
    int val2;

    ImportData(quint64 id) : tid(id) {}
};

class ImportDataController {
public:
    ImportDataController() {
        data.emplace(123, 123);
    }

    //1
    template<typename MemberType, typename T, typename = std::enable_if_t<std::is_convertible<T, MemberType>::value>>
    void setData(quint64 tid, MemberType ImportData::* mptr, T&& val) {
        auto iter = data.find(tid);
        if (iter == data.end())
            return;
        iter->second.*mptr = std::forward<T>(val);
    }

    //2
    void setOutReso(quint64 tid, const QString& val) {
        auto iter = data.find(tid);
        if (iter == data.end())
            return;
        iter->second.SrcReso = val;
    }

    //3
    void set(quint64 tid, const ImportData& val) {
        auto iter = data.find(tid);
        if (iter == data.end())
            return;
        iter->second = val;
    }


    const ImportData* get(quint64 tid) const {
        auto iter = data.find(tid);
        if (iter == data.end())
            return nullptr;
        return &iter->second;
    }

private:
    std::map<quint64, ImportData> data;
};

#endif // IMPORTDATA_H
