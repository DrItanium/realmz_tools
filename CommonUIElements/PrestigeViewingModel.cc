//
// Created by jwscoggins on 11/7/20.
//

#include "PrestigeViewingModel.h"
#include <QString>
#include <map>

enum class CharacterPrestigeFields {
    DamageTaken = 0,
    DamageGiven,
    HitsGiven,
    HitsTaken,
    MissedAttacks,
    DodgedAttacks,
    EnemiesKilled,
    TimesDied,
    TimesUnconscious,
    CombatSpellsCast,
    UndeadDestroyed,
    UndeadTurned,
    PenaltyPoints,
    TotalPrestige,
    Count,
};

std::map<CharacterPrestigeFields, QString> fieldNames {
        {CharacterPrestigeFields::PenaltyPoints, "Penalty Points"},
        {CharacterPrestigeFields::UndeadTurned, "Undead Turned"},
        {CharacterPrestigeFields::UndeadDestroyed, "Undead Destroyed"},
        {CharacterPrestigeFields::CombatSpellsCast,"Combat Spells Cast"},
        {CharacterPrestigeFields::TimesUnconscious, "Times Unconscious"},
        {CharacterPrestigeFields::TimesDied, "Times Died"},
        {CharacterPrestigeFields::EnemiesKilled, "Enemies Killed"},
        {CharacterPrestigeFields::DodgedAttacks, "Dodged Attacks"},
        {CharacterPrestigeFields::MissedAttacks, "Missed Attacks"},
        {CharacterPrestigeFields::HitsTaken, "Hits Taken"},
        {CharacterPrestigeFields::HitsGiven, "Hits Given"},
        {CharacterPrestigeFields::DamageGiven, "Damage Given"},
        {CharacterPrestigeFields::DamageTaken, "Damage Taken"},
        {CharacterPrestigeFields::TotalPrestige, "Total Prestige"},
};


int
PrestigeViewingModel::rowCount(const QModelIndex& idx) const {
    return static_cast<int>(CharacterPrestigeFields::Count);
}

QVariant
PrestigeViewingModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (!_cc)  {
            return QVariant();
        }
        auto mkStr = [](auto value) noexcept { return QString::number(static_cast<int>(value)); };
        const auto& pp = _cc->getPrestige();
        switch (static_cast<CharacterPrestigeFields>(index.row())) {
            case CharacterPrestigeFields::TotalPrestige: return mkStr(pp.getCurrentPrestige());
            case CharacterPrestigeFields::PenaltyPoints: return mkStr(pp.getPenaltyPoints());
            case CharacterPrestigeFields::UndeadTurned: return mkStr(pp.getUndeadTurned());
            case CharacterPrestigeFields::UndeadDestroyed: return mkStr(pp.getUndeadDestroyed());
            case CharacterPrestigeFields::CombatSpellsCast: return mkStr(pp.getCombatSpellsCast());
            case CharacterPrestigeFields::TimesUnconscious: return mkStr(pp.getTimesUnconscious());
            case CharacterPrestigeFields::TimesDied: return mkStr(pp.getTimesDied());
            case CharacterPrestigeFields::EnemiesKilled: return mkStr(pp.getEnemiesKilled());
            case CharacterPrestigeFields::DodgedAttacks: return mkStr(pp.getDodgedAttacks());
            case CharacterPrestigeFields::MissedAttacks: return mkStr(pp.getMissedAttacks());
            case CharacterPrestigeFields::HitsTaken: return mkStr(pp.getHitsTaken());
            case CharacterPrestigeFields::HitsGiven: return mkStr(pp.getHitsGiven());
            case CharacterPrestigeFields::DamageGiven: return mkStr(pp.getDamageGiven());
            case CharacterPrestigeFields::DamageTaken: return mkStr(pp.getDamageTaken());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant
PrestigeViewingModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Orientation::Vertical) {
            auto value = static_cast<CharacterPrestigeFields>(section);
            if (auto result = fieldNames.find(static_cast<CharacterPrestigeFields>(section)); result != fieldNames.end()) {
                return result->second;
            }
        }
    }
    return QVariant();
}
