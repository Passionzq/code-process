class Settings(object):

    def __init__(self):
        
        #screen setting
        self.screen_width = 900
        self.screen_height = 600
        self.bg_color = (250, 250, 250)

        #ship setting
        self.ship_limit = 3

        #bullet setting
        self.bullet_width = 3
        self.bullet_height = 10
        self.bullet_color = (60, 60, 60)
        self.bullet_alllowed = 3

        #alien setting
        self.fleet_drop_speed = 10

        #speed level
        self.speedup_scale = 1.1

        self.score_scale = 1.5

    def initialize_dymatic_settings(self):
        self.ship_speed_factor = 1.5
        self.bullet_speed_factor = 3
        self.alien_speed_factor = 1
        self.fleet_direction = 1
        self.alien_points = 50

    def increase_speed(self):
        self.ship_speed_factor *= self.speedup_scale
        self.bullet_speed_factor *= self.speedup_scale
        self.alien_speed_factor *= self.speedup_scale
        self.alien_points = int(self.alien_points * self.score_scale)
        print(self.alien_points)


        