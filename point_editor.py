import pygame
from sys import argv
from math import sqrt

def main() -> None:
    def distance(p1: int, p2: int) -> float:
        return sqrt((p2[0] - p1[0])**2 + (p2[1] - p2[1])**2)

    pygame.init()

    window = pygame.display.set_mode((950, 512))
    pygame.display.set_caption("Editor!")

    button_width = 40
    button_height = int(button_width * 16 / 9)
    print_button_rect = pygame.Rect(910, 0, button_width, button_height)
    clear_button_rect = pygame.Rect(
        910, button_height, button_width, button_height
    )
    write_button_rect = pygame.Rect(
        910, button_height * 2, button_width, button_height
    )

    lvl = argv[1]
    lvl_surf = pygame.image.load(f"assets/{lvl}")

    points = []

    running = True
    while running:
        window.fill((255, 255, 0))

        window.blit(lvl_surf, (0, 0))
        pygame.draw.rect(window, (0, 255, 0, 255), print_button_rect)
        pygame.draw.rect(window, (0, 255, 255, 255), clear_button_rect)
        pygame.draw.rect(window, (255, 0, 255, 255), write_button_rect)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == pygame.BUTTON_LEFT:
                    if event.pos[0] <= 910:
                        points.append(event.pos)
                    elif print_button_rect.collidepoint(event.pos):
                        print(points)
                    elif clear_button_rect.collidepoint(event.pos):
                        points.clear()
                    elif write_button_rect.collidepoint(event.pos):
                        with open("points.txt", "w") as out_file:
                            out_file.write('\n'.join(str(i) for i in points))
                    else:
                        with open("points.txt", "r") as in_file:
                            content = in_file.read()
                            exec(f"points = {content}")
                elif event.button == pygame.BUTTON_RIGHT:
                    for point in points:
                        dist = distance(point, event.pos)
                        if dist <= 5 and event.pos in points:
                            points.remove(event.pos)

        for point in points:
            pygame.draw.circle(window, (0, 0, 255, 255), point, 5)

        pygame.display.update()

    pygame.quit()


if __name__ == '__main__':
    main()