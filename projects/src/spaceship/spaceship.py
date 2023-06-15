import pygame
import sys
import random
import math
import mysql.connector
import datetime
import string
import time

# Initialize Pygame
pygame.init()


# Replace the connection details with your own
database = 'spaceship_scoring_board'
user = 'spaceship_user'
password = 'Evi1995!!'

# Establish the connection
conn = mysql.connector.connect(
    database=database,
    user=user,
    password=password
)

# Create a cursor object to execute SQL queries
cursor = conn.cursor()

# Define the INSERT statement
insert_query = """
INSERT INTO scoring (Player_Name, Score, Date, Hour)
VALUES (%s, %s, %s, %s)
"""

# Define the SELECT statement
score_query = """
SELECT score
FROM scoring
ORDER BY score DESC
LIMIT 5
"""

# Define the SELECT statement
names_query = """
SELECT Player_Name
FROM scoring
ORDER BY score DESC
LIMIT 5
"""


# Set up the display
width, height = 2000, 1600
screen = pygame.display.set_mode((width, height), pygame.FULLSCREEN)
pygame.display.set_caption("spaceship Game")

# Load spaceship image
spaceship_image = pygame.image.load("spaceship.png").convert_alpha()
spaceship_image = pygame.transform.scale(spaceship_image, (100, 100))
spaceship_rect = spaceship_image.get_rect()
spaceship_rect.center = (screen.get_width() // 2, 1000)

# Draw the rotated spaceship
rotated_spaceship_rect = spaceship_image.get_rect()
rotated_spaceship_rect.center = spaceship_rect.center


background_image = pygame.image.load("background.jpg").convert()
background_image = pygame.transform.scale(background_image, (screen.get_width(), screen.get_height()))

explosion_image = pygame.image.load("explosion.png").convert_alpha()
explosion_image = pygame.transform.scale(explosion_image, (300, 300))

bullet_image = pygame.image.load("bullet.png").convert_alpha()
bullet_image = pygame.transform.scale(bullet_image, (30, 30))

alien_image = pygame.image.load("alien.png").convert_alpha()
alien_image = pygame.transform.scale(alien_image, (50, 50))

font = pygame.font.Font(None, 80)


running = True
moving_rate = 3
base_moving_rate = moving_rate
bullet_speed = 5

rotate_angle = 0
angle_rate = 1

enter_key_pressed = False

is_exploding = False
explosion_duration = 0.5  
explosion_timer = 0.0
alien_timer = 0.0
spawn_interval = 0


current_time = 0

# Initializing list of Bullets
bullets = [] 
aliens = []

player_name = ""

def DisplayWelcomeScreen():
    text_surface = font.render("Insert your name: ", True, (255, 255, 255)) 
    text_surface2 = font.render(player_name, True, (255, 255, 255))  
    text_surface3 = font.render("Press Enter to start!", True, (255, 255, 255)) 

    screen.blit(background_image, (0,0))
    screen.blit(text_surface, (700, 100 ))
    screen.blit(text_surface2, (750, 170 ))
    screen.blit(text_surface3, (670, 300 ))

    cursor.execute(score_query)
    rows = cursor.fetchall()

    row_y = 700
    for row_score in rows:
        texted_row = font.render(str(row_score).strip(string.punctuation), True, (255, 255, 255))
        screen.blit(texted_row, (1100, row_y ))
        row_y += 60

    cursor.execute(names_query)
    rows = cursor.fetchall()

    row_y = 700
    for row_name in rows:
        texted_row = font.render(str(row_name).strip(string.punctuation), True, (255, 255, 255))
        screen.blit(texted_row, (600, row_y ))
        row_y += 60            

    pygame.display.flip()



class Alien:
    def __init__(self):
        self.random_x = random.randint(0, screen.get_width())
        self.random_y = random.randint(0, screen.get_height())

    def draw(self):
        self.alien_rect = alien_image.get_rect(center = (self.random_x , self.random_y))
        screen.blit(alien_image, self.alien_rect)

class Bullet:
    def __init__(self, x, y, angle):
        self.x = x
        self.y = y
        self.angle = angle
        self.speed = 5  
 
    def update(self):
        # Calculate the movement vector based on the angle
        movement_vector = pygame.math.Vector2(0, -self.speed).rotate(-self.angle)

        # Update the position of the bullet based on the movement vector
        self.x += movement_vector.x
        self.y += movement_vector.y

    def draw(self):
        self.rotate_bullet_image = pygame.transform.rotate(bullet_image, rotate_angle)
        self.bullet_rect = self.rotate_bullet_image.get_rect(center = (self.x, self.y))
        screen.blit(self.rotate_bullet_image, self.bullet_rect)


def DrawSpaceshipInSpace():
    # Draw the rotated spaceship
    rotated_spaceship_image = pygame.transform.rotate(spaceship_image, rotate_angle)
    rotated_spaceship_rect = rotated_spaceship_image.get_rect()
    rotated_spaceship_rect.center = spaceship_rect.center

    # Draw the background
    screen.blit(background_image, (0,0))
    screen.blit(rotated_spaceship_image, rotated_spaceship_rect)

def DrawScore(score):
    text_surface = font.render("Score:", True, (255, 255, 255))  # Text color is white (RGB: 255, 255, 255)
    text_surface2 = font.render(str(score), True, (255, 255, 255))  # Text color is white (RGB: 255, 255, 255)
    
    screen.blit(text_surface, (screen.get_width() // 2 - 70, 100 ))
    screen.blit(text_surface2, (screen.get_width() // 2, 170 ))

def DrawBullets():
    for bullet in bullets:
        bullet.draw()

    for bullet in bullets:
        if not screen.get_rect().colliderect(bullet.bullet_rect):
            bullets.remove(bullet)

def DrawAliens():
    for alien in aliens:
        alien.draw()

def HandleEndOfGame(score):
    values = (player_name.strip(), score, datetime.date.today(), datetime.datetime.now().time())
    cursor.execute(insert_query, values)
    conn.commit()
    cursor.close()
    conn.close()
    pygame.quit()
    sys.exit()

def CheckForCollision():
    for alien in aliens:
        distance = math.sqrt((rotated_spaceship_rect.x - alien.random_x)**2 + (rotated_spaceship_rect.y - alien.random_y)**2)
        if distance < 30: 
            HandleEndOfGame(score)


def CheckForDeadAliens(score):
    for bullet in bullets:
        for alien in aliens:
            distance = math.sqrt((bullet.x - alien.random_x)**2 + (bullet.y - alien.random_y)**2)
            if distance < 10: # threshold = 10
                bullets.remove(bullet)
                aliens.remove(alien)
                score += 10
    
    return score

score = 0

while running:

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN and enter_key_pressed == False:
            if event.key == pygame.K_BACKSPACE:
                player_name = player_name[:-1]
            elif event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
            else:
                player_name += event.unicode

    keys = pygame.key.get_pressed()

    if keys[pygame.K_RETURN]:
        enter_key_pressed = True

    if not enter_key_pressed:
        DisplayWelcomeScreen()

    else:
        movement_vector = pygame.math.Vector2(0, -moving_rate).rotate(-rotate_angle)

        spaceship_rect.y += movement_vector.y * (not is_exploding)
        spaceship_rect.x += movement_vector.x * (not is_exploding)

        for bullet in bullets:
            bullet.update()

        moving_rate = base_moving_rate

        if keys[pygame.K_UP]:
            moving_rate *= 1.5

        if keys[pygame.K_LEFT]:
            rotate_angle += angle_rate * (not is_exploding)

        if keys[pygame.K_RIGHT]:
            rotate_angle -= angle_rate * (not is_exploding)

        if keys[pygame.K_DOWN]:
            moving_rate = 1

        if keys[pygame.K_SPACE]:
            if len(bullets) < 70:
                bullets.append(Bullet(spaceship_rect.x, spaceship_rect.y, rotate_angle))
            
        if keys[pygame.K_ESCAPE]:
            pygame.quit()
            sys.exit()

        # Check if the spaceship is within the boundaries of the screen
        if not screen.get_rect().colliderect(spaceship_rect):
            is_exploding = True
            if explosion_timer == 0:
                explosion_timer = pygame.time.get_ticks() 

        current_time = pygame.time.get_ticks()

        if is_exploding:
            elapsed_time = (current_time - explosion_timer) / 1000.0  # Convert to seconds
            # Check if the explosion duration has elapsed
            if elapsed_time < explosion_duration:
                spaceship_image = explosion_image
                rotated_spaceship_image = pygame.transform.rotate(spaceship_image, 0)

            else:
                HandleEndOfGame(score)

        if spawn_interval == 0:
            spawn_interval = random.uniform(1, 2)
            alien_timer = pygame.time.get_ticks() 
        
        if spawn_interval < (current_time - alien_timer) / 1000.0:
            aliens.append(Alien())
            spawn_interval = 0

        score = CheckForDeadAliens(score)

        CheckForCollision()

        DrawSpaceshipInSpace()

        DrawScore(score)

        DrawBullets()

        DrawAliens()

        # Update the display
        pygame.display.flip()

 