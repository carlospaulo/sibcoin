#ifndef OFFERMODELEDITOR_H
#define OFFERMODELEDITOR_H

#include "offermodel.h"

class OfferModelEditor : public OfferModel<QtMyOfferInfo> {
    Q_OBJECT
public:
    OfferModelEditor(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

private:
    QString status(const StatusOffer &s) const;
};

#endif
