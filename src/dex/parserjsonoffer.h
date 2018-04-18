#ifndef PARSERJSONOFFER_H
#define PARSERJSONOFFER_H

#include "dex/db/dexdto.h"

namespace dex {

MyOfferInfo jsonToMyOfferInfo(const std::string &json, std::string &error);
std::pair<uint64_t, bool> priceFromString(std::string strPrice);
int numberSings(const std::string &str);

}

#endif
