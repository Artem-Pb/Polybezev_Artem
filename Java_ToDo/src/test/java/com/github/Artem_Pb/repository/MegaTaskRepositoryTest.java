package com.github.Artem_Pb.repository;

import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.SimpleTask;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import static org.assertj.core.api.Assertions.assertThat;

// @DataJpaTest — поднимает только JPA слой: сущности, репозитории, H2 в памяти.
// Без контроллеров, без сервисов. Каждый тест оборачивается в транзакцию и откатывается — база чистая.
@DataJpaTest
class MegaTaskRepositoryTest {

    @Autowired
    private MegaTaskRepository megaTaskRepository;

    @Autowired
    private SimpleTaskRepository simpleTaskRepository;

    @Test
    void deleteMegaTask_cascadesSubTasks() {
        // Arrange — создаём MegaTask с двумя сабтасками.
        MegaTask mega = new MegaTask("Project");
        mega.addSubTask(new SimpleTask("Sub 1"));
        mega.addSubTask(new SimpleTask("Sub 2"));
        mega = megaTaskRepository.save(mega);
        Long megaId = mega.getId();

        // Проверяем что сабтаски реально сохранились.
        assertThat(simpleTaskRepository.findAll()).hasSize(2);

        // Act — удаляем мегатаск.
        megaTaskRepository.deleteById(megaId);

        // Assert — и мегатаск и сабтаски должны исчезнуть (CascadeType.ALL + orphanRemoval).
        assertThat(megaTaskRepository.findById(megaId)).isEmpty();
        assertThat(simpleTaskRepository.findAll()).isEmpty();
    }

    @Test
    void saveMegaTask_subTasksPersistedWithParent() {
        MegaTask mega = new MegaTask("Big task");
        mega.addSubTask(new SimpleTask("Step 1"));
        mega.addSubTask(new SimpleTask("Step 2"));
        megaTaskRepository.save(mega);

        MegaTask found = megaTaskRepository.findAll().get(0);

        assertThat(found.getTitle()).isEqualTo("Big task");
        assertThat(found.getSubTasks()).hasSize(2);
    }
}
