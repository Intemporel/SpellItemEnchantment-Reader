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
    quint32 record = data->searchRecordByID(3402);

    if (record) {
        QVector<quint32> stat_type = data->getStatType(record);

        qDebug() << record;

        for (int i = 0; i <stat_type.size(); i++)
            qDebug() << stat_type[i];
    }


    return a.exec();
}
