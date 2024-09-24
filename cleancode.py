from dataclasses import dataclass

@dataclass
class Person:
    name: str
    age: int


@dataclass
class Page:
    title: str
    content: str

    @classmethod
    def from_person(cls, person: Person):
        return Page(
            title=f'{person.name}',
            content=f'{person.name}, Idade: {person.age}'
        )

def render_html(page: Page):

    title = page.title
    body = f'{page.title} Idade: {page.content}'
    html = f'''
    <html>
        <head>
            <title>{page.title}</title>
        </head>
        <body>
            <h1>{page.title}</h1>
            <section>
                {page.content}
            </section>
        </body>
    </html>
    '''

p = Person("Fulano", 25)
page = Page.from_person(p)
print(render_html(page))

# python cleancode.py > index.html
# firefox index.html