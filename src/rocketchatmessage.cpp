/*
   Copyright (c) 2017 Montel Laurent <montel@kde.org>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   ( at your option ) version 3 or, at the discretion of KDE e.V.
   ( which shall act as a proxy as in section 14 of the GPLv3 ), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#include "rocketchatmessage.h"

#include <QJsonArray>
#include <QJsonObject>

RocketChatMessage::RocketChatMessage()
    : mJsonFormat(QJsonDocument::Compact)
{

}

void RocketChatMessage::setJsonFormat(const QJsonDocument::JsonFormat &jsonFormat)
{
    mJsonFormat = jsonFormat;
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::getRoomRoles(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("getRoomRoles"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::eraseRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("eraseRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::archiveRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("archiveRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::unarchiveRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("unarchiveRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::openRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("openRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::leaveRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("leaveRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::hideRoom(const QString &roomID, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID)};
    return generateMethod(QStringLiteral("hideRoom"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::toggleFavorite(const QString &roomID, bool favorite, quint64 id)
{
    const QJsonArray params{QJsonValue(roomID), {favorite}};
    return generateMethod(QStringLiteral("toggleFavorite"), QJsonDocument(params), id);
}

RocketChatMessage::RocketChatMessageResult RocketChatMessage::generateMethod(const QString &method, const QJsonDocument &params, quint64 id)
{
    QJsonObject json;
    json[QStringLiteral("msg")] = QStringLiteral("method");
    json[QStringLiteral("method")] = method;
    json[QStringLiteral("id")] = QString::number(id);

    if (params.isArray()) {
        json[QStringLiteral("params")] = params.array();
    } else if (params.isObject()) {
        QJsonArray arr;
        arr.append(params.object());
        json[QStringLiteral("params")] = arr;
    }
    const QString generatedJsonDoc = QString::fromUtf8(QJsonDocument(json).toJson(mJsonFormat));
    RocketChatMessageResult result;
    result.jsonDocument = params;
    result.method = method;
    result.result = generatedJsonDoc;
    return result;
}

