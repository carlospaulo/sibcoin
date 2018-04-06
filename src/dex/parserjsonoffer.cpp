#include <univalue.h>
#include "util.h"
#include "parserjsonoffer.h"
#include "db/countryiso.h"
#include "db/currencyiso.h"

MyOfferInfo jsonToMyOfferInfo(const std::string &json, std::string &error)
{
    MyOfferInfo offer;

    UniValue uv(UniValue::VOBJ);
    uv.read(json);

    std::string strType = uv["type"].get_str();

    if (strType != "buy" && strType != "sell") {
        error = "offer type is empty";
        return MyOfferInfo();
    }

    offer.type = Buy;
    if (strType == "sell") {
        offer.type = Sell;
    }

    offer.countryIso = uv["countryIso"].get_str();
    dex::CountryIso countryiso;
    if (!countryiso.isValid(offer.countryIso)) {
        error = "invalid country code";
        return MyOfferInfo();
    }

    offer.currencyIso = uv["currencyIso"].get_str();
    dex::CurrencyIso currencyiso;
    if (!currencyiso.isValid(offer.currencyIso)) {
        error = "invalid currency code";
        return MyOfferInfo();
    }

    offer.paymentMethod = uv["paymentMethod"].get_int();
    if (offer.paymentMethod != 1 && offer.paymentMethod != 128) {
        error = "invalid paymentMethod";
        return MyOfferInfo();
    }

    auto price = priceFromString(uv["price"].get_str());

    if (!price.second) {
        error = "invalid price";
        return MyOfferInfo();
    }

    offer.price = price.first;

    auto minAmount = priceFromString(uv["minAmount"].get_str());

    if (!minAmount.second) {
        error = "invalid minAmount";
        return MyOfferInfo();
    }

    offer.minAmount = minAmount.first;

    offer.timeCreate = GetTime();
    int timeTo = uv["timeToExpiration"].get_int();
    if (timeTo != 10 && timeTo != 20 && timeTo != 30) {
        error = "invalid timeExpiration";
        return MyOfferInfo();
    }

    offer.timeToExpiration = offer.timeCreate + timeTo * 86400;

    offer.shortInfo = uv["shortInfo"].get_str();

    if (offer.shortInfo.size() > 140) {
        error = "invalid shortInfo";
        return MyOfferInfo();
    }

    offer.details = uv["details"].get_str();

    return offer;
}

std::pair<uint64_t, bool> priceFromString(std::string strPrice)
{
    bool isCorrect = true;
    std::size_t found = strPrice.find(".");
    if (found != std::string::npos) {
        std::string i = strPrice.substr(0, found);
        std::string f = strPrice.substr(found + 1);

        if (f.length() < numberOfDecimalsForPrice) {
            int size = numberOfDecimalsForPrice-f.size();
            for (int i = 0; i< size; i++) {
                f.push_back('0');
            }
        } else if (f.length() > numberOfDecimalsForPrice) {
            isCorrect = false;
        }
        
        strPrice = i + f;
    } else {
        std::string zero = std::string(numberOfDecimalsForPrice, '0');
        strPrice += zero;
    }

    uint64_t price = std::strtoull(strPrice.c_str(), nullptr, 10);
    return std::make_pair(price, isCorrect);
}
