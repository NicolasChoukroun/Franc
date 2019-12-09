// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FRANC_QT_FRANCADDRESSVALIDATOR_H
#define FRANC_QT_FRANCADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class francAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit francAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** franc address widget validator, checks for a valid franc address.
 */
class francAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit francAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // FRANC_QT_FRANCADDRESSVALIDATOR_H
