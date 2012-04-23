#ifndef H_POWER_H
#define H_POWER_H

/* Health */
void power_health_player(int h);
void power_health_world(int h);

/* Death */
void power_death_player();

/* Powerup effects */
void power_powerup_player(unsigned char type);
void power_process_powerup();

/* Invencible status */
void power_set_invencible();
int power_is_invencible();
void power_refresh_invencible(Uint32 delta);

#endif
