#include "spell_item_enchantment_reader.h"
#include <sstream>
#include <iostream>

spell_item_enchantment_reader::spell_item_enchantment_reader(QString file){
    // only read SpellItemEnchantment.dbc
    if (not file.contains("SpellItemEnchantment")) {
        delete this;
        return;
    }

    this->setFileName(file);
    this->open(QIODevice::ReadOnly);

    buffer = readAll();

    // header
    magic             = buffer.mid(0,LENGTH);
    record_count      = ValueFrom(LENGTH*1);
    field_count       = ValueFrom(LENGTH*2);
    record_size       = ValueFrom(LENGTH*3);
    string_block_size = ValueFrom(LENGTH*4);

    // only read dbc file
    if (magic.toStdString() != "WDBC")
        delete this;

}

QString spell_item_enchantment_reader::reverseHex(QByteArray bytes){
    QString reverse;
    QString hex [4];

    for (int i = 0; i < 4; i ++)
        hex[i] = QString("%1%2").arg(bytes.toHex()[0+(2*i)]).arg(bytes.toHex()[1+(2*i)]);

    for (int i = 3 ; i >= 0 ; i -- )
        reverse.push_back(hex[i]);

    return reverse;
}

quint32 spell_item_enchantment_reader::searchRecordByID(uint valueToFound){
    quint32 record = 0;
    quint32 position;

    for (quint32 i = 0 ; i < record_count ; i++) {
        position = HEADER_SIZE + (i*record_size);

        if (valueToFound == ValueFrom(position))
            return i;
    }

    return record;
}

quint32 spell_item_enchantment_reader::ValueFrom(quint32 pos) {
    return strHexToUint32(reverseHex(buffer.mid(pos,LENGTH)));
}

quint32 spell_item_enchantment_reader::ValueWhere(quint32 record, quint32 field) {
    return ValueFrom(HEADER_SIZE + (record*record_size) + (LENGTH*field));
}

QVector<quint32> spell_item_enchantment_reader::getStatType(quint32 record){
    quint32 position = HEADER_SIZE + (record*record_size) + (LENGTH*SpellItemEnchantmentStructure::OBJECT_ID_1);
    QVector<quint32> toReturn;

    for (int i = 0; i < 3; i ++) {
        toReturn.push_back(ValueFrom(position));
        position+=4;
    }

    return toReturn;
}
