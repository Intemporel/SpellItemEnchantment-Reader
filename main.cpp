#include <QApplication>
#include <SpellItemEnchantmentReader/spell_item_enchantment_reader.h>

#include <QDebug>
#include <QFile>
#include <QDataStream>

spell_item_enchantment_reader * data;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    data = new spell_item_enchantment_reader(":/binary/dbc/enUS/SpellItemEnchantment.dbc");
    quint32 record = data->searchRecordByID(266);
    qDebug() << "Current cell [" << record << "]";

    if (record) {
        QVector<quint32> stat_key = data->getStatKey(record);
        QVector<quint32> stat_type = data->getStatType(record);
        QVector<QVector<quint32>> stat_value = data->getStatValue(record);

        QString text = data->getText(record);
        qDebug() << "String [" << text << "]";

        for (int i = 0; i <stat_type.size(); i++)
            qDebug() << "Key [" << stat_key[i] << "] : Type [" << stat_type[i] << "] : Min,Max - [" << stat_value[i][0] << "," << stat_value[i][1] << "]";
    }


    return a.exec();
}
